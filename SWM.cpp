// Sliding Window Minimum data structure
// Supports 3 deque operations and allows to retrieve the minimum of the stored values, all in Ө(1).
template<typename T>
struct SWM{
  deque<T> dq_have, dq_f;

  bool swm_comparator(T value1, T value2){
    return value1 <= value2; // Default: minimum. For maximum change to "value1 >= value2".
    // The comparator should return True for equal elements.
  }

  void push_back(T value){
    while (!dq_f.empty() && !swm_comparator(dq_f.back(), value)) dq_f.pop_back();
    dq_have.push_back(value), dq_f.push_back(value);
  }

  void push_front(T value){
    if (dq_f.empty() || swm_comparator(value, dq_f.front())) dq_f.push_front(value);
    dq_have.push_front(value);
  }

  void pop_front(){
    assert(!dq_f.empty());
    if (dq_have.front() == dq_f.front()) dq_f.pop_front();
    dq_have.pop_front();
  }

  T get(){
    assert(!dq_f.empty());
    return dq_f.front();
  }

  void clear(){
    dq_have.clear(), dq_f.clear();
  }
};
