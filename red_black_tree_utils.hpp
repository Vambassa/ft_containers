#ifndef RED_BLACK_TREE_UTILS_HPP
#define RED_BLACK_TREE_UTILS_HPP

namespace ft {

	enum RBTColor { Black, Red };

	template <class T>
	struct RBTNode
	{
		T			value;
		RBTColor	color;
		RBTNode		*left;
		RBTNode		*right;
		RBTNode		*parent;

		RBTNode(const T& value, RBTColor color = Red, RBTNode *left = NULL,
			 RBTNode *right = NULL, RBTNode *parent = NULL) :
			 value(value), color(color), left(left), right(right), parent(parent) {};
	};
}

# endif
