// implement min-priority Queue using min-heap
#include <iostream>
#include <climits>
using namespace std;

class PriorityQueue
{
    int *arr;
    int capacity;
    int size;

    public:
        PriorityQueue(int capacity)
        {
            this->capacity = capacity;
            arr = new int[capacity];
            size = 0;
        }

        int parent(int i)
        {
            return (i - 1) / 2;
        }

        int left(int i)
        {
            return 2 * i + 1;
        }

        int right(int i)
        {
            return 2 * i + 2;
        }

        void insert(int x)
        {
            if(size == capacity)
            {
                cout << "Overflow" << endl;
                return;
            }

            size++;
            int i = size - 1;
            arr[i] = x;

            while(i != 0 and arr[parent(i)] > arr[i])
            {
                swap(arr[parent(i)], arr[i]);
                i = parent(i);
            }
        }

        void decreaseKey(int i, int x)
        {
            arr[i] = x;

            while(i != 0 and arr[parent(i)] > arr[i])
            {
                swap(arr[parent(i)], arr[i]);
                i = parent(i);
            }
        }

        int extractMin()
        {
            if(size <= 0)
                return INT_MAX;

            if(size == 1)
            {
                size--;
                return arr[0];
            }

            int root = arr[0];
            arr[0] = arr[size - 1];
            size--;
            heapify(0);

            return root;
        }

        void heapify(int i)
        {
            int l = left(i);
            int r = right(i);
            int smallest = i;

            if(l < size and arr[l] < arr[smallest])
                smallest = l;

            if(r < size and arr[r] < arr[smallest])
                smallest = r;

            if(smallest != i)
            {
                swap(arr[i], arr[smallest]);
                heapify(smallest);
            }
        }

        void deleteKey(int i)
        {
            decreaseKey(i, INT_MIN);
            extractMin();
        }

        int getMin()
        {
            return arr[0];
        }
};

int main()
{
    PriorityQueue pq(10);

    pq.insert(3);
    pq.insert(2);
    pq.deleteKey(1);
    pq.insert(15);
    pq.insert(5);
    pq.insert(4);
    pq.insert(45);

    cout << "Min via ExtractMin : " << pq.extractMin() << endl;
    cout << "Min via getMin : " << pq.getMin() << endl;
    pq.decreaseKey(2, 1);
    cout << "Min via getMin after decreaseKey : " << pq.getMin() << endl;

    return 0;
}