"""
Implementation of k-nearest neighbours classifier
"""

from re import X
import numpy as np

from collections import Counter

import utils
from utils import euclidean_dist_squared


class KNN:
    X = None
    y = None

    def __init__(self, k):
        self.k = k

    def fit(self, X, y):
        self.X = X  # just memorize the training data
        self.y = y

#NOTE: in case I forget to declare elsewhere, I used a youtube video from "Python Engineer"'s youtube channel for help with this.

    def predict(self, X_hat):
        distances = utils.euclidean_dist_squared(X_hat, self.X)
        predicted_labels = [self._predict(x) for x in distances]

        return np.array(predicted_labels)

    def _predict(self, x):
        #get distances to this point        
        #get k nearest samples, labels
        k_indices = np.argsort(x)[:self.k]
        k_nearest_labels = [self.y[i] for i in k_indices]

        #majority vote 
        most_common = Counter(k_nearest_labels).most_common(1)
        return most_common[0][0]
