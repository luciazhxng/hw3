#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>

template <typename T, typename Comparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m = 2, Comparator c = Comparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;
  void print();

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;
  int m_; 
  Comparator c_;

};


template <typename T, typename Comparator>
void Heap<T,Comparator>::print() {
  for(int i = 0; i < data.size(); i++) {
    std::cout << std::to_string(data[i]) + " ";
  }
  std::cout << std::endl;
}


// Add implementation of member functions here
template <typename T, typename Comparator>
Heap<T,Comparator>::Heap(int m, Comparator c) {
  m_ = m;
  c_ = c;
}
template <typename T, typename Comparator>
Heap<T,Comparator>::~Heap() {
  
}
template <typename T, typename Comparator>
bool Heap<T, Comparator>::empty() const {
  if(size() == 0) {
    return true;
  }
  return false;
}

template <typename T, typename Comparator>
size_t Heap<T, Comparator>::size() const {
  return data.size();
}
template <typename T, typename Comparator>
void Heap<T, Comparator>::push(const T& item)
{
  data.push_back(item);
  int index = data.size() - 1;
  // std::cout <<index<<std::endl;
  while(index != 0) {
    int parent_i = (index - 1) / 2;
    T& curr = data[index];
    // std::cout <<"curr "<<curr<<std::endl;
    T& parent = data[parent_i];
    // std::cout <<"parent "<<parent<<std::endl;
    if(c_(curr, parent)) {
      // std::cout <<"comparator"<<std::endl;
      T temp = data[index]; 
      data[index] = parent;
      data[parent_i] = temp;
      index  = parent_i;
    }
    else {
      break;
    }
  }
}
// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
T const & Heap<T, Comparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::underflow_error("heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
void Heap<T, Comparator>::pop()
{
  if(empty()){
    throw std::underflow_error("heap is empty");
  }

  data[0] = data[data.size() - 1];
  data.pop_back();
  int size = data.size();

  int curr_index = 0;
  bool swapped;

  while(true) {
    swapped = false;
    int left_index = 2 * curr_index +1;
    int right_index = 2 * curr_index + 2;
    T& curr = data[curr_index];
    T& left = data[left_index];
    T& right = data[right_index];
    if((left_index < size) && (right_index < size)) {
      if(c_(left, curr) && c_(right, curr)) {
        if(c_(left, right)) {
          T temp = data[left_index];
          data[left_index] = curr;
          data[curr_index] = temp;
          curr_index = left_index;
          swapped = true;
        }
        else {
          T temp = data[right_index];
          data[right_index] = curr;
          data[curr_index] = temp;
          curr_index = right_index;
          swapped = true;
        }
      }
      else if(c_(left, curr)) {
        T temp = data[left_index];
        data[left_index] = curr;
        data[curr_index] = temp;
        curr_index = left_index;
        swapped = true;
      }
      else if(c_(right, curr)) {
        T temp = data[right_index];
        data[right_index] = curr;
        data[curr_index] = temp;
        curr_index = right_index;
        swapped = true;
      }
    }
    else if((left_index < size) && c_(left,curr)) {
      T temp = data[left_index];
      data[left_index] = curr;
      data[curr_index] = temp;
      curr_index = left_index;
      swapped = true;
    }
    else if((right_index < size) && c_(right,curr)) {
      T temp = data[right_index];
      data[right_index] = curr;
      data[curr_index] = temp;
      curr_index = right_index;
      swapped = true;
    }
    if(swapped == false) {
      break;
    }
  }
}



#endif

