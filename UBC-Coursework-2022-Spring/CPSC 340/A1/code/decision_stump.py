import numpy as np
import utils


class DecisionStumpEquality:
    """
    This is a decision stump that branches on whether the value of X is
    "almost equal to" some threshold.

    This probably isn't a thing you want to actually do, it's just an example.
    """

    y_hat_yes = None
    y_hat_no = None
    j_best = None
    t_best = None

    def fit(self, X, y):
        n, d = X.shape

        # Get an array with the number of 0's, number of 1's, etc.
        count = np.bincount(y)

        # Get the index of the largest value in count.
        # Thus, y_mode is the mode (most popular value) of y
        y_mode = np.argmax(count)

        self.y_hat_yes = y_mode
        self.y_hat_no = None
        self.j_best = None
        self.t_best = None

        # If all the labels are the same, no need to split further
        if np.unique(y).size <= 1:
            return

        minError = np.sum(y != y_mode)

        # Loop over features looking for the best split
        for j in range(d):
            for i in range(n):
                # Choose value to equate to
                t = np.round(X[i, j])

                # Find most likely class for each split
                is_almost_equal = np.round(X[:, j]) == t
                y_yes_mode = utils.mode(y[is_almost_equal])
                y_no_mode = utils.mode(y[~is_almost_equal])  # ~ is "logical not"

                # Make predictions
                y_pred = y_yes_mode * np.ones(n)
                y_pred[np.round(X[:, j]) != t] = y_no_mode

                # Compute error
                errors = np.sum(y_pred != y)

                # Compare to minimum error so far
                if errors < minError:
                    # This is the lowest error, store this value
                    minError = errors
                    self.j_best = j
                    self.t_best = t
                    self.y_hat_yes = y_yes_mode
                    self.y_hat_no = y_no_mode

    def predict(self, X):
        n, d = X.shape
        X = np.round(X)

        if self.j_best is None:
            return self.y_hat_yes * np.ones(n)

        y_hat = np.zeros(n)

        for i in range(n):
            if X[i, self.j_best] == self.t_best:
                y_hat[i] = self.y_hat_yes
            else:
                y_hat[i] = self.y_hat_no

        return y_hat


class DecisionStumpErrorRate:
    longitude_best_split = None
    latitude_best_split = None

    longitude_lowest_error = None
    latitude_lowest_error = None

    def fit(self, X, y):
        n, d = X.shape

        # Get the range of long and lat
        lowest_long = np.min(X[:,0])
        highest_long = np.max(X[:,0])
        lowest_lat = np.min(X[:,1])
        highest_lat = np.max(X[:,1])

        #set minError(s) start to maximum possible errors
        minError_lat = np.size(y)
        minError_long = np.size(y)

        # Loop over values looking for the best split in LONGITUDE
        for longitude_split in np.arange(lowest_long,highest_long,0.5):
            
            # Find most likely class for each split
            is_west_of = X[:,0]>longitude_split

            # Make predictions
            y_pred_long = np.ones(n)
            y_pred_long[is_west_of[:] == 1] = 0

            # Compute error
            errors = np.sum(y_pred_long != y)

            # Compare to minimum error so far
            if errors < minError_long:
                # This is the lowest error, store this value
                minError_long = errors
                self.longitude_best_split = longitude_split
                self.longitude_lowest_error= minError_long
            
        for latitude_split in np.arange(lowest_lat,highest_lat,0.5):
            
            # Find most likely class for each split
            is_north_of = X[:,1]>latitude_split

            # Make predictions
            y_pred_lat = np.ones(n)
            y_pred_lat[is_north_of[:] == 1] = 0

            # Compute error
            errors = np.sum(y_pred_lat != y)

            # Compare to minimum error so far
            if errors < minError_lat:
                # This is the lowest error, store this value
                minError_lat = errors
                self.latitude_best_split = latitude_split
                self.latitude_lowest_error= minError_lat


    def predict(self, X):
        n, d = X.shape
        X = np.round(X)

        split_value = None

        if self.longitude_best_split is None:
            print("error: no longitude best split")
            return np.ones(n)
        
        if self.latitude_best_split is None:
            print("error: no latitude best split")
            return np.ones(n)
        
        if self.longitude_lowest_error <= self.latitude_lowest_error:
            long_vs_lat = 0
            split_value = self.longitude_best_split
        else: 
            long_vs_lat = 1
            split_value = self.latitude_best_split

        y_hat = np.ones(n)

        for i in range(n):
            if X[i, long_vs_lat] > split_value:
                y_hat[i] = 0


        return y_hat
   



def entropy(p):
    """
    A helper function that computes the entropy of the
    discrete distribution p (stored in a 1D numpy array).
    The elements of p should add up to 1.
    This function ensures lim p-->0 of p log(p) = 0
    which is mathematically true, but numerically results in NaN
    because log(0) returns -Inf.
    """
    plogp = 0 * p  # initialize full of zeros
    plogp[p > 0] = p[p > 0] * np.log(p[p > 0])  # only do the computation when p>0
    return -np.sum(plogp)


class DecisionStumpInfoGain(DecisionStumpErrorRate):
    # This is not required, but one way to simplify the code is
    # to have this class inherit from DecisionStumpErrorRate.
    # Which methods (init, fit, predict) do you need to overwrite?

    longitude_best_split = None
    latitude_best_split = None

    longitude_lowest_entropy = None
    latitude_lowest_entropy = None

    def fit(self, X, y):
        n, d = X.shape


        # Get the range of long and lat
        lowest_long = np.min(X[:,0])
        highest_long = np.max(X[:,0])
        lowest_lat = np.min(X[:,1])
        highest_lat = np.max(X[:,1])

        #set minEntropy(s) start to start at 1
        minInfoGain_lat = 0
        minInfoGain_long = 0


        # Loop over values looking for the best split in LONGITUDE
        for longitude_split in np.arange(lowest_long,highest_long,0.5):
            
            # Find all cities west of split
            is_west_of = X[:,0]>longitude_split

            #Find Entropy of both sides
            num_cities_west = np.bincount(is_west_of,minlength=2)
            entropy_west = np.zeros(num_cities_west[1])
            entropy_east = np.zeros(num_cities_west[0])

            #indexes for entropy west and east
            j = 0
            k = 0

            for i in range(n):
                if (is_west_of[i]==1):
                    entropy_west[j]=y[i]
                    j += 1
                else:
                    entropy_east[k]=y[i]
                    k += 1
            
            
            #normalize vector sent to entropy
            entropy_west = entropy_west/num_cities_west[1]
            entropy_east = entropy_east/num_cities_west[0]


            # Calculate Entropy
            cur_entropy_west = entropy(entropy_west)
            cur_entropy_east = entropy(entropy_east)
            cur_entropy_total_long = 1-(np.size(entropy_west)/n)*cur_entropy_west + (np.size(entropy_east)/n)*cur_entropy_east

            # Compare to minimum etropy so far
            if cur_entropy_total_long < minInfoGain_long:
                # This is the lowest error, store this value
                minInfoGain_long = cur_entropy_total_long
                self.longitude_best_split = longitude_split
                self.longitude_lowest_entropy= cur_entropy_total_long
            
        for latitude_split in np.arange(lowest_lat,highest_lat,0.5):
            
            # Find most likely class for each split
            is_north_of = X[:,1]>latitude_split

           
            #Find Entropy of both sides
            num_cities_north = np.bincount(is_north_of,minlength=2)
            entropy_north = np.zeros(num_cities_north[1])
            entropy_south = np.zeros(num_cities_north[0])
            
            #indexes for entropy west and east
            j = 0
            k = 0

            for i in range(n):
                if (is_north_of[i]==1):
                    entropy_north[j]=y[i]
                    j += 1
                else:
                    entropy_south[k]=y[i]
                    k += 1
            
            #normalize vector sent to entropy
            entropy_north = entropy_north/num_cities_north[1]
            entropy_south = entropy_south/num_cities_north[0]
            
            # Calculate Entropy
            cur_entropy_north = entropy(entropy_north)
            cur_entropy_south = entropy(entropy_south)
            cur_entropy_total_lat = 1-(np.size(entropy_north)/n)*cur_entropy_north + (np.size(entropy_south)/n)*cur_entropy_south

            # Compare to minimum etropy so far
            if cur_entropy_total_lat < minInfoGain_lat:
                # This is the lowest error, store this value
                minInfoGain_lat = cur_entropy_total_lat
                self.latitude_best_split = latitude_split
                self.latitude_lowest_entropy= cur_entropy_total_lat


    def predict(self, X):
        n, d = X.shape
        X = np.round(X)

        split_value = None

        if self.longitude_best_split is None:
            print("error: no longitude best split")
            return np.ones(n)
        
        if self.latitude_best_split is None:
            print("error: no latitude best split")
            return np.ones(n)
        
        if self.longitude_lowest_entropy <= self.latitude_lowest_entropy:
            long_vs_lat = 0
            split_value = self.longitude_best_split
        else: 
            long_vs_lat = 1
            split_value = self.latitude_best_split

        y_hat = np.ones(n)

        for i in range(n):
            if X[i, long_vs_lat] > split_value:
                y_hat[i] = 0


        return y_hat
