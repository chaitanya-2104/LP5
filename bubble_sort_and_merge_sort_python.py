import time
import numpy as np

def bubble_sort(arr):
  n = len(arr)
  for i in range(n-1):
    for j in range(n-i-1):
      if arr[j] > arr[j+1]:
        arr[j], arr[j+1] = arr[j+1], arr[j]
def merge_sort(arr):
  if len(arr) <= 1:
    return arr
  mid = len(arr) // 2
  left = merge_sort(arr[:mid])
  right = merge_sort(arr[mid:])
  return merge(left, right)
def merge(left, right):
  result = []
  i = 0
  j = 0
  while i < len(left) and j < len(right):
    if left[i] <= right[j]:
      result.append(left[i])
      i += 1
    else:
      result.append(right[j])
      j += 1
  result += left[i:]
  result += right[j:]
  return result

arr =[10,2,3,4,5,6,8,4,4,7,33,3]*100

start = time.time()
bubble_sort(arr)
end = time.time()
print("Sequential bubble sort time:", end-start)
start = time.time()
merge_sort(arr)
end = time.time()
print("Sequential merge sort time:", end-start)
# Parallel bubble sort
num_threads = 4
start = time.time()
for i in range(num_threads):
    start_index = i * len(arr) // num_threads
    end_index = (i+1) * len(arr) // num_threads
    bubble_sort(arr[start_index:end_index])
end = time.time()
print("Parallel bubble sort time:", end-start)
# Parallel merge sort
start = time.time()
l=[]
for i in range(num_threads):
    start_index = i * len(arr) // num_threads
    end_index = (i+1) * len(arr) // num_threads
    merge_sort(arr[start_index:end_index])

end = time.time()
print("Parallel merge sort time:", end-start)