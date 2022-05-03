#!/usr/bin/env python
import argparse
from audioop import avg
import os
import pickle
from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier

# make sure we're working in the directory this file lives in,
# for imports and for simplicity with relative paths
os.chdir(Path(__file__).parent.resolve())

# our code
from utils import load_dataset, plot_classifier, handle, run, main
from decision_stump import DecisionStumpInfoGain
from decision_tree import DecisionTree
from kmeans import Kmeans
from knn import KNN
from naive_bayes import NaiveBayes, NaiveBayesLaplace
from random_tree import RandomForest, RandomTree


@handle("1")
def q1():
    dataset = load_dataset("citiesSmall.pkl")

    X = dataset["X"]
    y = dataset["y"]
    X_test = dataset["Xtest"]
    y_test = dataset["ytest"]

    """YOUR CODE HERE FOR Q1"""

    #TRAINING RUNS
    model = KNN(1)
    model.fit(X,y)
    predictions = model.predict(X)
    tscore1 = np.sum(predictions == y) / len(y)
    print("The training error for K=1 is: ", 1- tscore1)

    model = KNN(3)
    model.fit(X,y)
    predictions = model.predict(X)
    tscore2 = np.sum(predictions == y) / len(y)
    print("The training error for K=3 is: ", 1- tscore2)

    model = KNN(10)
    model.fit(X,y)
    predictions = model.predict(X)
    tscore3 = np.sum(predictions == y) / len(y)
    print("The training error for K=10 is: ",1-  tscore3)


    #TEST RUNS
    model = KNN(1)
    model.fit(X,y)
    predictions = model.predict(X_test)
    score1 = np.sum(predictions == y_test) / len(y_test)
    print("The error for K=1 is: ", 1- score1)

    model = KNN(3)
    model.fit(X,y)
    predictions = model.predict(X_test)
    score2 = np.sum(predictions == y_test) / len(y_test)
    print("The error for K=3 is: ", 1- score2)

    model = KNN(10)
    model.fit(X,y)
    predictions = model.predict(X_test)
    score3 = np.sum(predictions == y_test) / len(y_test)
    print("The error for K=10 is: ", 1- score3)


    model=KNN(1)
    model.fit(X,y)
    plot_classifier(model, X, y)

    fname = Path("..", "figs", "q1_decisionBoundary.pdf")
    plt.savefig(fname)
    print("\nFigure saved as '%s'" % fname)

    pass



@handle("2")
def q2():
    dataset = load_dataset("ccdebt.pkl")
    X = dataset["X"]
    y = dataset["y"]
    X_test = dataset["Xtest"]
    y_test = dataset["ytest"]

    ks = list(range(1, 30, 4))
    """YOUR CODE HERE FOR Q2"""

    # #get value for 1/10th size of training set
    # ten_pc = len(y)*.1
    # #set up array for results
    # k_results = []
    # for k in ks:    
    # #set up mask array for each cross validation with a single k
    #     avg_score = 0
    #     for i in range(0,9):
    #         mask = np.ones(len(y))
    #         for j in range(int(i*ten_pc),int((i+1)*(ten_pc))):
    #             mask[j]=0 



    # #once mask array is set, copy all training data into a new array 9/10 the size
    #         X_iter_training_data = [x for ind, x in enumerate(X) if mask[ind]==1]
    #         y_iter_training_labels = [y for ind, y in enumerate(y) if mask[ind]==1]
    #         X_iter_test_data = [x for ind, x in enumerate(X) if mask[ind]==0]
    #         y_iter_test_labels = [y for ind, y in enumerate(y) if mask[ind]==0]
    #         print(X_iter_test_data)
    #         # for l in range(0,len(mask)):
    #         #     if mask[l] == 1:
    #         #         X_iter_training_data = np.append(X_iter_training_data, X[l])
    #         #         y_iter_training_labels = np.append(y_iter_training_labels, y[l])
    #         #     if mask[l]==0:
    #         #         X_iter_test_data = np.append(X_iter_test_data, X[l])
    #         #         y_iter_test_labels = np.append(y_iter_test_labels, y[l])

    # #now that I have training data, create+fit model and 
    #         model = KNN(k)
    #         model.fit(X_iter_training_data, y_iter_training_labels)
    # # predict with a given k. Then score it.
    #         predictions = model.predict(X_iter_test_data)
    #         score = np.sum(predictions == y_iter_test_labels) / len(y_iter_test_labels)
    
    # #need to find avg score for the cross vaidation
    #         avg_score = avg_score + score

    #     avg_score = avg_score/10

    # #now store the avg in the k
    #     k_results.append(avg_score)

    # print(k_results)


    pass



@handle("3.2")
def q3_2():
    dataset = load_dataset("newsgroups.pkl")

    X = dataset["X"].astype(bool)
    y = dataset["y"]
    X_valid = dataset["Xvalidate"]
    y_valid = dataset["yvalidate"]
    groupnames = dataset["groupnames"]
    wordlist = dataset["wordlist"]

    """YOUR CODE HERE FOR Q3.2"""




    pass



@handle("3.3")
def q3_3():
    dataset = load_dataset("newsgroups.pkl")

    X = dataset["X"]
    y = dataset["y"]
    X_valid = dataset["Xvalidate"]
    y_valid = dataset["yvalidate"]

    print(f"d = {X.shape[1]}")
    print(f"n = {X.shape[0]}")
    print(f"t = {X_valid.shape[0]}")
    print(f"Num classes = {len(np.unique(y))}")

    model = NaiveBayes(num_classes=4)
    model.fit(X, y)

    y_hat = model.predict(X)
    err_train = np.mean(y_hat != y)
    print(f"Naive Bayes training error: {err_train:.3f}")

    y_hat = model.predict(X_valid)
    err_valid = np.mean(y_hat != y_valid)
    print(f"Naive Bayes validation error: {err_valid:.3f}")


@handle("3.4")
def q3_4():
    dataset = load_dataset("newsgroups.pkl")

    X = dataset["X"]
    y = dataset["y"]
    X_valid = dataset["Xvalidate"]
    y_valid = dataset["yvalidate"]

    print(f"d = {X.shape[1]}")
    print(f"n = {X.shape[0]}")
    print(f"t = {X_valid.shape[0]}")
    print(f"Num classes = {len(np.unique(y))}")

    model = NaiveBayes(num_classes=4)
    model.fit(X, y)

    """YOUR CODE HERE FOR Q3.4"""
    raise NotImplementedError()



@handle("4")
def q4():
    dataset = load_dataset("vowel.pkl")
    X = dataset["X"]
    y = dataset["y"]
    X_test = dataset["Xtest"]
    y_test = dataset["ytest"]
    print(f"n = {X.shape[0]}, d = {X.shape[1]}")

    def evaluate_model(model):
        model.fit(X, y)

        y_pred = model.predict(X)
        tr_error = np.mean(y_pred != y)

        y_pred = model.predict(X_test)
        te_error = np.mean(y_pred != y_test)
        print(f"    Training error: {tr_error:.3f}")
        print(f"    Testing error: {te_error:.3f}")

    print("Decision tree info gain")
    evaluate_model(DecisionTree(max_depth=np.inf, stump_class=DecisionStumpInfoGain))

    """YOUR CODE FOR Q4"""
    pass



@handle("5")
def q5():
    X = load_dataset("clusterData.pkl")["X"]

    model = Kmeans(k=4)
    model.fit(X)
    y = model.predict(X)
    plt.scatter(X[:, 0], X[:, 1], c=y, cmap="jet")

    fname = Path("..", "figs", "kmeans_basic_rerun.png")
    plt.savefig(fname)
    print(f"Figure saved as {fname}")


@handle("5.1")
def q5_1():
    X = load_dataset("clusterData.pkl")["X"]

    """YOUR CODE HERE FOR Q5.1"""
    raise NotImplementedError()



@handle("5.2")
def q5_2():
    X = load_dataset("clusterData.pkl")["X"]

    """YOUR CODE HERE FOR Q5.2"""
    raise NotImplementedError()



# if __name__ == "__main__":
#     main()
