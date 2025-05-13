#ifndef MAXBINARYHEAP_H
#define MAXBINARYHEAP_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class HeapNodeMax {
public:
    string month;
    string artist;
    string title;
    string label;
    int year;
    int weeks;

    HeapNodeMax (string mon, int yr, string singer, string song, string house, int noWeeks)
        : month(mon), year(yr), artist(singer), title(song),
          label(house), weeks(noWeeks) {}

    string getData() const {
        return month + " | " + to_string(year) + " | " + artist + " | " +
               title + " | " + label + " | " + to_string(weeks) + "\n";
    }
};

class MaxBinaryHeap {
private:
    vector<HeapNodeMax> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIdx = (index - 1) / 2;
            if (heap[index].weeks > heap[parentIdx].weeks) {
                swap(heap[index], heap[parentIdx]);
                index = parentIdx;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int leftChild, rightChild, largest;
        int size = heap.size();

        while (index < size) {
            leftChild = 2 * index + 1;
            rightChild = 2 * index + 2;
            largest = index;

            if (leftChild < size && heap[leftChild].weeks > heap[largest].weeks)
                largest = leftChild;

            if (rightChild < size && heap[rightChild].weeks > heap[largest].weeks)
                largest = rightChild;

            if (largest != index) {
                swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    MaxBinaryHeap() {}

    void insert(string mon, int yr, string singer, string song, string house, int noWeeks) {
        HeapNodeMax newNode(mon, yr, singer, song, house, noWeeks);
        heap.push_back(newNode);
        heapifyUp(heap.size() - 1);
    }

    HeapNodeMax extractMax() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        HeapNodeMax maxNode = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return maxNode;
    }

    bool isEmpty() const {
        return heap.empty();
    }

    string printHeap() const {
        string output;
        for (const auto& node : heap) {
            output += node.getData();
        }
        return output;
    }
};

#endif
