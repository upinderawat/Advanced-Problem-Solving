def partition(arr, l, r):
    pivot = l
    for i in range(l+1, r+1):
        if arr[i] <= arr[l]:
            pivot += 1
            arr[i], arr[pivot] = arr[pivot], arr[i]
    arr[pivot], arr[l] = arr[l], arr[pivot]
    return pivot


def quicksort(arr, l, r):
    if l >= r:
        return
    pivot = partition(arr, l, r)
    quicksort(arr, l, pivot-1)
    quicksort(arr, pivot+1, r)

