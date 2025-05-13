#ifndef MINBINARYHEAP_H
#define MINBINARYHEAP_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class HeapNode {
public:
    string month;
    string artist;
    string title;
    string label;
    int year;
    int weeks;

    HeapNode(string mon, int yr, string singer, string song, string house, int noWeeks)
        : month(mon), year(yr), artist(singer), title(song),
          label(house), weeks(noWeeks) {}

    string getData() const {
        return month + " | " + to_string(year) + " | " + artist + " | " +
               title + " | " + label + " | " + to_string(weeks) + "\n";
    }
};

class MinBinaryHeap {
private:
    vector<HeapNode> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIdx = (index - 1) / 2;
            if (heap[index].weeks < heap[parentIdx].weeks) {
                swap(heap[index], heap[parentIdx]);
                index = parentIdx;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int leftChild, rightChild, smallest;
        int size = heap.size();

        while (index < size) {
            leftChild = 2 * index + 1;
            rightChild = 2 * index + 2;
            smallest = index;

            if (leftChild < size && heap[leftChild].weeks < heap[smallest].weeks)
                smallest = leftChild;

            if (rightChild < size && heap[rightChild].weeks < heap[smallest].weeks)
                smallest = rightChild;

            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }

public:
    MinBinaryHeap() {}

    void insert(string mon, int yr, string singer, string song, string house, int noWeeks) {
        HeapNode newNode(mon, yr, singer, song, house, noWeeks);
        heap.push_back(newNode);
        heapifyUp(heap.size() - 1);
    }

    HeapNode extractMin() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        HeapNode minNode = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return minNode;
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
