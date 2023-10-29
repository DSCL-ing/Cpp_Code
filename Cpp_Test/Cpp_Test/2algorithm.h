#pragma once


//sotr
/**
 * 
template <class RandomAccessIterator>
  void sort (RandomAccessIterator first, RandomAccessIterator last);
template <class RandomAccessIterator, class Compare>
  void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
 * 
 * 默认是升序，降序需要反函数
 * 内部是快排
 * 
 * 使用
 * 正序:  std::sort(begin() ,end() );
 * 降序:  
 * #include<functional>
 * greater<int> g;
 * 1.std::sort(begin() ,end() , g);
 * 2.std::sort(begin() ,end() , greater<int>());
 * 
 */


//find


