import numpy as np

#sigmoid function
def sigmoid(X):
   return 1/(1+np.exp(-X))

theta1 = np.array([[1,1,2.4],[1,1.7,3.2]])
theta2 = np.array([1,-0.2,-1.7])

swap_theta1 = np.array([[1,1.7,3.2],[1,1,2.4]])
swap_theta2 = np.array([1,-1.7,-0.2])

inputX = np.array([[1],[3],[4]])

outputX = sigmoid(np.dot(theta1,inputX))
swap_outputX = sigmoid(np.dot(swap_theta1,inputX))

print(outputX)
print(swap_outputX)

