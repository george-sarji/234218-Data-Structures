# Requested functions:

## Init:
Initializes an empty structure
Complexity: O(1)

## AddCarType:
Adds a new car type to the dealership
Complexity: O(log(n) + M) => n = number of current types, m = number of models (parameter)

## RemoveCarType:
Removes given car ID from dealership
Complexity: O(log(n) + mlog(M)) => n = number of current types, M = total number of models, m = number of cars removed

## SellCar:
Sells a car from the dealership
Complexity: O(log(n) + log(M)) => n = number of current types, M = total number of models

## MakeComplaint:
Sends a complaint about given model
Complexity: O(log(M)) => M = total number of models

## GetBestSellerModelByType:
Gets the best selling model from the given type
Complexity: O(log(n)) => n = number of current types

## GetWorstModels:
Gets a given number of the worst models
Complexity: O(m) => m = number of models (parameter)

## Quit:
Releases all the memory used by the memory
Complexity: O(n + m) => n = number of current types, m = total number of cars in dealership