#include <ctime>
#include <iostream>

#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "set.hpp"

#include <stack>
#include <vector>
#include <map>
#include <set>

// Vector Test

template<class T>
static void print_vector(const ft::vector<T> &v) {
	for (size_t i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl << std::endl;
}

static void vector_test() {
	clock_t vector_start = clock();

	ft::vector<int> v1;
	std::cout << "v1 capacity: " << v1.capacity() << std::endl;
	std::cout << "v1 size: " << v1.size() << std::endl;
	std::cout << "v1 empty: " << (v1.empty() == 1 ? "true" : "false") << std::endl << std::endl;

	for (int i = 0; i < 16; ++i) {
		v1.push_back(i * 2);
	}
	std::cout << "v1: ";
	print_vector(v1);

	ft::vector<int>::iterator a = v1.begin();
	for (; a != v1.end(); ++a)
		*a /= 2;
	std::cout << "v1 / 2 : ";
	print_vector(v1);

	ft::vector<int>::reverse_iterator b = v1.rbegin();
	std::cout << "v1 reverse_iterator: ";
	for (; b != v1.rend(); ++b)
		std::cout << *b << " ";
	std::cout << std::endl << std::endl;

	std::cout << "v1 capacity: " << v1.capacity() << std::endl;
	std::cout << "v1 size: " << v1.size() << std::endl;
	std::cout << "v1 empty: " << (v1.empty() == 1 ? "true" : "false") << std::endl << std::endl;


	ft::vector<int> v2(v1.rbegin(), v1.rend());
	std::cout << "v2 (reversed v1): ";
	print_vector(v2);

	std::cout << "v1[4]: " << v1.at(4) << std::endl;
	try {
		std::cout << "v1[20]: " << v1.at(20) << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "v1[4]: " << v1[4] << std::endl;
	std::cout << "v1 front: " << v1.front() << std::endl;
	std::cout << "v1 back: " << v1.back() << std::endl;
	std::cout << "v1 data: " << *v1.data() << std::endl << std::endl;

	v1.clear();
	std::cout << "v1 empty after clear: " << (v1.empty() == 1 ? "true" : "false") << std::endl;

	v1.insert(v1.begin(), v2.begin() + 5, v2.end());
	std::cout << "v1 insert from v2: ";
	print_vector(v1);

	v1.erase(v1.begin() + 1);
	std::cout << "v1 after erasing 1 element: ";
	print_vector(v1);

	v1.push_back(100);
	std::cout << "v1 push_back 100: ";
	print_vector(v1);
	v1.pop_back();
	std::cout << "v1 pop_back: ";
	print_vector(v1);

	v1.resize(20, 0);
	std::cout << "v1 after resizing to 20: ";
	print_vector(v1);

	std::cout << "v1 == v2: " << (v1 == v2 ? "true" : "false") << std::endl;
	std::cout << "v1 < v2: " << (v1 < v2 ? "true" : "false") << std::endl;

	std::vector<int> p;
	for (int i = 0; i < 100000; ++i) {
		p.push_back(i);
	}

	clock_t vector_end = clock();
	printf("Execution time for my vector: %.2fms\n",
		   (double) (vector_end - vector_start) / CLOCKS_PER_SEC * 1000);
}

template<class T>
static void print_stl_vector(const std::vector <T> &v) {
	for (size_t i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl << std::endl;
}

static void stl_vector_test() {
	clock_t vector_start = clock();

	std::vector<int> v1;
	std::cout << "v1 capacity: " << v1.capacity() << std::endl;
	std::cout << "v1 size: " << v1.size() << std::endl;
	std::cout << "v1 empty: " << (v1.empty() == 1 ? "true" : "false") << std::endl << std::endl;

	for (int i = 0; i < 16; ++i) {
		v1.push_back(i * 2);
	}
	std::cout << "v1: ";
	print_stl_vector(v1);

	std::vector<int>::iterator a = v1.begin();
	for (; a != v1.end(); ++a)
		*a /= 2;
	std::cout << "v1 / 2 : ";
	print_stl_vector(v1);

	std::vector<int>::reverse_iterator b = v1.rbegin();
	std::cout << "v1 reverse_iterator: ";
	for (; b != v1.rend(); ++b)
		std::cout << *b << " ";
	std::cout << std::endl << std::endl;

	std::cout << "v1 capacity: " << v1.capacity() << std::endl;
	std::cout << "v1 size: " << v1.size() << std::endl;
	std::cout << "v1 empty: " << (v1.empty() == 1 ? "true" : "false") << std::endl << std::endl;


	std::vector<int> v2(v1.rbegin(), v1.rend());
	std::cout << "v2 (reversed v1): ";
	print_stl_vector(v2);

	std::cout << "v1[4]: " << v1.at(4) << std::endl;
	try {
		std::cout << "v1[20]: " << v1.at(20) << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "v1[4]: " << v1[4] << std::endl;
	std::cout << "v1 front: " << v1.front() << std::endl;
	std::cout << "v1 back: " << v1.back() << std::endl;
	std::cout << "v1 data: " << *v1.data() << std::endl << std::endl;

	v1.clear();
	std::cout << "v1 empty after clear: " << (v1.empty() == 1 ? "true" : "false") << std::endl;

	v1.insert(v1.begin(), v2.begin() + 5, v2.end());
	std::cout << "v1 insert from v2: ";
	print_stl_vector(v1);

	v1.erase(v1.begin() + 1);
	std::cout << "v1 after erasing 1 element: ";
	print_stl_vector(v1);

	v1.push_back(100);
	std::cout << "v1 push_back 100: ";
	print_stl_vector(v1);
	v1.pop_back();
	std::cout << "v1 pop_back: ";
	print_stl_vector(v1);

	v1.resize(20, 0);
	std::cout << "v1 after resizing to 20: ";
	print_stl_vector(v1);

	std::cout << "v1 == v2: " << (v1 == v2 ? "true" : "false") << std::endl;
	std::cout << "v1 < v2: " << (v1 < v2 ? "true" : "false") << std::endl;

	std::vector<int> p;
	for (int i = 0; i < 100000; ++i) {
		p.push_back(i);
	}

	clock_t vector_end = clock();
	printf("Execution time for stl vector: %.2fms\n",
		   (double) (vector_end - vector_start) / CLOCKS_PER_SEC * 1000);
}

// Stack Test

static void stack_test() {
	clock_t stack_start = clock();

	ft::stack<int> st1;
	std::cout << "st1 size: " << st1.size() << std::endl;
	std::cout << "st1 empty: " << (st1.empty() == 1? "true" : "false") << std::endl << std::endl;
	for (int i = 0; i < 100000; ++i) {
		st1.push(i);
	}
	std::cout << "st1 top: " << st1.top() << std::endl;
	std::cout << "st1 empty: " << (st1.empty() == 1 ? "true" : "false") << std::endl;
	std::cout << "st1 size: " << st1.size() << std::endl << std::endl;

	ft::stack<int> st2 = st1;
	std::cout << "st2 size: " << st2.size() << std::endl << std::endl;
	st2.push(333);
	std::cout << "st2 top: " << st2.top() << std::endl;
	std::cout << "st2 size: " << st2.size() << std::endl << std::endl;

	std::cout << "st2 == st1: " << (st2 == st1 ? "true" : "false") << std::endl;
	std::cout << "st2 >= st1: " << (st2 >= st1 ? "true" : "false") << std::endl << std::endl;

	st2.pop();
	std::cout << "st2 top: " << st2.top() << std::endl;
	std::cout << "st2 != st1: " << (st2 != st1 ? "true" : "false") << std::endl;

	clock_t stack_end = clock();
	printf("Execution time for my stack: %.2fms\n",
		   (double) (stack_end - stack_start) / CLOCKS_PER_SEC * 1000);
}

static void stl_stack_test() {
	clock_t stack_start = clock();

	std::stack<int> st1;
	std::cout << "st1 size: " << st1.size() << std::endl;
	std::cout << "st1 empty: " << (st1.empty() == 1? "true" : "false") << std::endl << std::endl;
	for (int i = 0; i < 100000; ++i) {
		st1.push(i);
	}
	std::cout << "st1 top: " << st1.top() << std::endl;
	std::cout << "st1 empty: " << (st1.empty() == 1 ? "true" : "false") << std::endl;
	std::cout << "st1 size: " << st1.size() << std::endl << std::endl;

	std::stack<int> st2 = st1;
	std::cout << "st2 size: " << st2.size() << std::endl << std::endl;
	st2.push(333);
	std::cout << "st2 top: " << st2.top() << std::endl;
	std::cout << "st2 size: " << st2.size() << std::endl << std::endl;

	std::cout << "st2 == st1: " << (st2 == st1 ? "true" : "false") << std::endl;
	std::cout << "st2 >= st1: " << (st2 >= st1 ? "true" : "false") << std::endl << std::endl;

	st2.pop();
	std::cout << "st2 top: " << st2.top() << std::endl;
	std::cout << "st2 != st1: " << (st2 != st1 ? "true" : "false") << std::endl;

	clock_t stack_end = clock();
	printf("Execution time for stl stack: %.2fms\n",
	       (double) (stack_end - stack_start) / CLOCKS_PER_SEC * 1000);
}

// Map Test

static void print_map(const ft::map<std::string, int> &m) {
	std::cout << "{ ";
	ft::map<std::string, int>::const_iterator it = m.begin();
	for (; it != m.end(); ++it) {
		std::cout << it->first << ": " << it->second << ' ';
	}
	std::cout << "}\n\n";
}

void map_test() {
	clock_t map_start = clock();

	ft::map<std::string, int> m1;
	m1["aaa"] = 1;
	m1["bbb"] = 22;
	m1["ccc"] = 333;
	m1["ddd"] = 4444;
	std::cout << "m1: ";
	print_map(m1);
	std::cout << "insert \"eee = 55555\" successfully: " <<
		(m1.insert(ft::make_pair("eee", 55555)).second == 1 ?  "true" : "false") << std::endl;
	std::cout << "m1: ";
	print_map(m1);
	std::cout << "insert \"eee = 0\" successfully: " <<
	          (m1.insert(ft::make_pair("eee", 0)).second == 1 ?  "true" : "false") << std::endl;
	std::cout << "m1: ";
	print_map(m1);

	m1["eee"] = 5;
	std::cout << "m1 changed \"eee\"-value to 5: ";
	print_map(m1);

	ft::map<std::string, int> m2(m1.find("bbb"), m1.end());
	std::cout << "m2: ";
	print_map(m2);

	std::cout << "m2.at(\"bbb\"): " << m2.at("bbb") << std::endl;
	try {
		std::cout << "m2.at(\"world\"): " << m2.at("world") << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "m2[bbb]: " << m2["bbb"] << std::endl << std::endl;

	std::cout << "m1 empty: " << (m1.empty() ? "true" : "false") << std::endl;
	std::cout << "m1 size: " << m1.size() << std::endl << std::endl;

	m1.clear();
	std::cout << "m1 size after clearing: " << m1.size() << std::endl;
	std::cout << "m1 empty: " << (m1.empty() ? "true" : "false") << std::endl;

	m2.erase(m2.find("ccc"));
	std::cout << "m2 after erasing \"ccc\": ";
	print_map(m2);
	std::cout << "m2 size: " << m2.size() << std::endl;

	ft::map<std::string, int> m3(m2);
	std::cout << "m3: ";
	print_map(m3);

	std::cout << "m2 == m3: " << (m2 == m3 ? "true" : "false") << std::endl;
	std::cout << "m2 >= m3: " << (m2 >= m3 ? "true\n" : "false\n") << std::endl;

	ft::map<std::string, int>::reverse_iterator a = m2.rbegin();
	for (; a != m2.rend(); ++a)
		(*a).second = 1;
	std::cout << "m2 changed value: ";
	print_map(m2);

	std::cout << "m2 == m3: " << (m2 == m3 ? "true\n" : "false\n") << std::endl;

	ft::map<int, int> m4;
	for (int i = 0; i < 10000; ++i) {
		m4.insert(ft::make_pair(i, i * 2));
	}
	std::cout << "m4 count 10: " << m4.count(10) << std::endl;
	std::cout << "m4 find 1 (value): " << m4.find(1)->second << std::endl;
	std::cout << "lower bound 5: " << m4.lower_bound(5)->first << std::endl;
	std::cout << "upper bound 5: " << m4.upper_bound(5)->first << std::endl << std::endl;

	clock_t map_end = clock();
	printf("Execution time for my map: %.2fms\n",
		   (double) (map_end - map_start) / CLOCKS_PER_SEC * 1000);
}

static void print_stl_map(const std::map<std::string, int> &m) {
	std::cout << "{ ";
	std::map<std::string, int>::const_iterator it = m.begin();
	for (; it != m.end(); ++it) {
		std::cout << it->first << ": " << it->second << ' ';
	}
	std::cout << "}\n\n";
}

void stl_map_test() {
	clock_t map_start = clock();

	std::map<std::string, int> m1;
	m1["aaa"] = 1;
	m1["bbb"] = 22;
	m1["ccc"] = 333;
	m1["ddd"] = 4444;
	std::cout << "m1: ";
	print_stl_map(m1);
	std::cout << "insert \"eee = 55555\" successfully: " <<
	          (m1.insert(std::make_pair("eee", 55555)).second == 1 ?  "true" : "false") << std::endl;
	std::cout << "m1: ";
	print_stl_map(m1);
	std::cout << "insert \"eee = 0\" successfully: " <<
	          (m1.insert(std::make_pair("eee", 55555)).second == 1 ?  "true" : "false") << std::endl;
	std::cout << "m1: ";
	print_stl_map(m1);

	m1["eee"] = 5;
	std::cout << "m1 changed \"eee\"-value to 5: ";
	print_stl_map(m1);

	std::map<std::string, int> m2(m1.find("bbb"), m1.end());
	std::cout << "m2: ";
	print_stl_map(m2);


	std::cout << "m2.at(\"bbb\"): " << m2.at("bbb") << std::endl;
	try {
		std::cout << "m2.at(\"world\"): " << m2.at("world") << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "m2[bbb]: " << m2["bbb"] << std::endl << std::endl;

	std::cout << "m1 empty: " << (m1.empty() ? "true" : "false") << std::endl;
	std::cout << "m1 size: " << m1.size() << std::endl << std::endl;

	m1.clear();
	std::cout << "m1 size after clearing: " << m1.size() << std::endl;
	std::cout << "m1 empty: " << (m1.empty() ? "true" : "false") << std::endl;

	m2.erase(m2.find("ccc"));
	std::cout << "m2 after erasing \"ccc\": ";
	print_stl_map(m2);

	std::map<std::string, int> m3(m2);
	std::cout << "m3: ";
	print_stl_map(m3);

	std::cout << "m2 == m3: " << (m2 == m3 ? "true" : "false") << std::endl;
	std::cout << "m2 >= m3: " << (m2 >= m3 ? "true\n" : "false\n") << std::endl;

	std::map<std::string, int>::reverse_iterator a = m2.rbegin();
	for (; a != m2.rend(); ++a)
		(*a).second = 1;
	std::cout << "m2 changed value: ";
	print_stl_map(m2);

	std::cout << "m2 == m3: " << (m2 == m3 ? "true\n" : "false\n") << std::endl;

	std::map<int, int> m4;
	for (int i = 0; i < 10000; ++i) {
		m4.insert(std::make_pair(i, i * 2));
	}
	std::cout << "m4 count 10: " << m4.count(10) << std::endl;
	std::cout << "m4 find 1 (value): " << m4.find(1)->second << std::endl;
	std::cout << "lower bound 5: " << m4.lower_bound(5)->first << std::endl;
	std::cout << "upper bound 5: " << m4.upper_bound(5)->first << std::endl << std::endl;

	clock_t map_end = clock();
	printf("Execution time for stl map: %.2fms\n",
	       (double) (map_end - map_start) / CLOCKS_PER_SEC * 1000);
}

// Set Test

static void print_set(const ft::set<int> &s) {
	std::cout << "{ ";
	ft::set<int>::const_iterator it = s.begin();
	for (; it != s.end(); ++it)
		std::cout << *it << ' ';
	std::cout << "}\n\n";
}

void set_test() {
	clock_t set_start = clock();

	ft::set<int> s1;
	for (int i = 0; i < 10; ++i)
		s1.insert(i * 3);
	std::cout << "s1: ";
	print_set(s1);

	ft::set<int> s3 = s1;

	ft::set<int>::reverse_iterator a = s1.rbegin();
	std::cout << "s1 reversed: { ";
	for (; a != s1.rend(); ++a) {
		std::cout << *a << ' ';
	}
	std::cout << "}\n\n";

	ft::set<int> s2(s1.find(15), s1.end());
	std::cout << "s2 inserted from s1: ";
	print_set(s2);

	std::cout << "s2 empty: " << (s2.empty() ? "true" : "false") << std::endl;
	std::cout << "s2 size: " << s2.size() << std::endl << std::endl;

	s2.clear();
	std::cout << "s2 empty after clearing: " << (s2.empty() ? "true\n" : "false\n") << std::endl;

	s1.erase(s1.find(15));
	s1.erase(27);
	std::cout << "s1 after erasing 15, 27: ";
	print_set(s1);

	std::cout << "s3: ";
	print_set(s3);

	s1.swap(s3);
	std::cout << "s3: ";
	print_set(s3);

	std::cout << "s1 == s3: " << (s1 == s3 ? "true" : "false") << std::endl;
	std::cout << "s1 < s3: " << (s1 < s3 ? "true\n" : "false\n") << std::endl;
	
	for (int i = 0; i < 100000; ++i) {
		s2.insert(i * 2);
	}
	std::cout << "count 5: " << s2.count(5) << std::endl;
	std::cout << "find 10: " << *s2.find(10) << std::endl;
	std::cout << "lower bound 10: " << *s2.lower_bound(10) << std::endl;
	std::cout << "upper bound 10: " << *s2.upper_bound(10) << std::endl << std::endl;

	clock_t set_end = clock();
	printf("Execution time for my set: %.2fms\n",
		   (double) (set_end - set_start) / CLOCKS_PER_SEC * 1000);
}

static void print_stl_set(const std::set<int> &s) {
	std::cout << "{ ";
	std::set<int>::const_iterator it = s.begin();
	for (; it != s.end(); ++it)
		std::cout << *it << ' ';
	std::cout << "}\n\n";
}

void stl_set_test() {
	clock_t set_start = clock();

	std::set<int> s1;
	for (int i = 0; i < 10; ++i)
		s1.insert(i * 3);
	std::cout << "s1: ";
	print_stl_set(s1);

	std::set<int> s3 = s1;

	std::set<int>::reverse_iterator a = s1.rbegin();
	std::cout << "s1 reversed: { ";
	for (; a != s1.rend(); ++a) {
		std::cout << *a << ' ';
	}
	std::cout << "}\n\n";

	std::set<int> s2(s1.find(15), s1.end());
	std::cout << "s2 inserted from s1: ";
	print_stl_set(s2);

	std::cout << "s2 empty: " << (s2.empty() ? "true" : "false") << std::endl;
	std::cout << "s2 size: " << s2.size() << std::endl << std::endl;

	s2.clear();
	std::cout << "s2 empty after clearing: " << (s2.empty() ? "true\n" : "false\n") << std::endl;

	s1.erase(s1.find(15));
	s1.erase(27);
	std::cout << "s1 after erasing 15, 27: ";
	print_stl_set(s1);

	std::cout << "s3: ";
	print_stl_set(s3);

	s1.swap(s3);
	std::cout << "s3: ";
	print_stl_set(s3);

	std::cout << "s1 == s3: " << (s1 == s3 ? "true" : "false") << std::endl;
	std::cout << "s1 < s3: " << (s1 < s3 ? "true\n" : "false\n") << std::endl;

	for (int i = 0; i < 100000; ++i) {
		s2.insert(i * 2);
	}
	std::cout << "count 5: " << s2.count(5) << std::endl;
	std::cout << "find 10: " << *s2.find(10) << std::endl;
	std::cout << "lower bound 10: " << *s2.lower_bound(10) << std::endl;
	std::cout << "upper bound 10: " << *s2.upper_bound(10) << std::endl << std::endl;

	clock_t set_end = clock();
	printf("Execution time for stl set: %.2fms\n",
	       (double) (set_end - set_start) / CLOCKS_PER_SEC * 1000);
}

int main() {
	std::cout << "----- VECTOR TEST -----\n" << std::endl;
	vector_test();
	std::cout << std::endl << std::endl;

	std::cout << "----- STL VECTOR TEST -----\n" << std::endl;
	stl_vector_test();
	std::cout << std::endl << std::endl;

	std::cout << "----- STACK TEST -----\n" << std::endl;
	stack_test();
	std::cout << std::endl << std::endl;

	std::cout << "----- STL STACK TEST -----\n" << std::endl;
	stl_stack_test();
	std::cout << std::endl << std::endl;

	std::cout << "----- MAP TEST -----\n" << std::endl;
	map_test();
	std::cout << std::endl << std::endl;

	std::cout << "----- STL MAP TEST -----\n" << std::endl;
	stl_map_test();
	std::cout << std::endl << std::endl;

	std::cout << "----- SET TEST -----\n" << std::endl;
	set_test();
	std::cout << std::endl << std::endl;

	std::cout << "----- STL SET TEST -----\n" << std::endl;
	stl_set_test();
	std::cout << std::endl;

	return 0;
}