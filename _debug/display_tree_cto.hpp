#ifndef AVL_DISPLAY_HPP
# define AVL_DISPLAY_HPP
# include "Node.hpp" 
# include <cmath>
# include <iomanip>
# include <vector>
# include <iostream>
# define PARENT 'p'
# define LEFT 'l'
# define RIGHT 'r'

template<typename K, typename V>
class MapDisplayIterator
{
	private:
		Node<K, V>*	ptr;
		char		last;

		void	go_up(void)
		{
			last = LEFT;
			if (ptr->parent_node()->right_node() == ptr)
			{
				last = RIGHT;
				col -= pow(2, height - level);
				level--;
				ptr = ptr->parent_node();
				return ;
			}
			else
			{
				col += pow(2, height - level);
				level--;
				ptr = ptr->parent_node();
				return ;
			}
		}

		void	go_left(void)
		{
			last = PARENT;
			level++;
			col -= pow(2, height - level);
			ptr = ptr->left_node();
		}

		void	go_right(void)
		{
			last = PARENT;
			level++;
			col += pow(2, height - level);
			ptr = ptr->right_node();
		}

	public:
		size_t	level;
		size_t	col;
		size_t	height;
		MapDisplayIterator(Node<K, V>* node)
		{
			level = 0;
			height = node->height();
			while (node->left_node())
			{
				node = node->left_node();
				level++;
			}
			last = PARENT;
			ptr = node;
			col = 0;
		}
		~MapDisplayIterator(void){}

		class NullPtrException : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{ return "NULL POINTER EXCEPTION"; }
		};

		Node<K, V>&	operator*(void)
		{
			if (!ptr)
				throw NullPtrException();
			return *ptr;
		}

		void	operator++(void)
		{
			if (!ptr)
				return ;
			if (last == PARENT)
			{
				if (ptr->left_node())
				{
					while (ptr->left_node())
						this->go_left();
					return ;
				}
				else if (ptr->right_node())
				{
					this->go_right();
					while (ptr->left_node())
						this->go_left();
					return ;
				}
			}
			else if (last == LEFT)
			{
				if (ptr->right_node())
				{
					this->go_right();
					if (ptr->left_node())
					{
						while (ptr->left_node())
							this->go_left();
					}
					return ;
				}
			}
			else
			{
				std::cout << "WTF JUST HAPPENED" << std::endl;
				return ;
			}
			if (ptr->parent_node())
			{
				if (ptr->parent_node()->right_node() == ptr)
				{
					while (ptr->parent_node() && ptr->parent_node()->right_node() == ptr)
						this->go_up();
					if (!ptr->parent_node()->parent_node())
					{
						ptr = NULL;
						return ;
					}
					this->go_up();
				}
				else if (ptr->parent_node()->left_node() == ptr && ptr->parent_node()->parent_node())
				{
					this->go_up();
					return ;
				}
			}
			return ;
		}
};

template<typename K, typename V>
void	display_tree(Node<K, V>* root)
{
	size_t	k = 0;
	size_t	height = 1 + root->height();
	size_t*	tab[height][(int)(pow(2, height) - 1)];
	for (size_t j = 0 ; j < height ; j++)
	{
		for (size_t i = 0; i < (pow(2, height) - 1) ; i++)
			tab[j][i] = NULL;
	}
	MapDisplayIterator<size_t, char>	iter(root);
	for (size_t i = 0; i < (pow(2, height) - 1) ; i++)
	{
		try {
			k = (*iter).key();
			long long int b = (*iter).balanceFactor();
			if (b > 1 || b < -1)
			{
				if (k != 999)
					std::cerr << "/!\\ UNBALANCED NODE /!\\" << std::endl;
			}
			tab[iter.level][iter.col] = new size_t((*iter).key());
		}
		catch (std::exception& e)
		{ break ; }
		++iter;
	}
	for (size_t j = 0 ; j < height ; j++)
	{
		for (size_t i = 0; i < (pow(2, height) - 1) ; i++)
		{
			if (tab[j][i])
				std::cout << "[" << std::setw(2) << std::setfill(' ') << *(tab[j][i]) << "]";
			else
				std::cout << " " << std::setw(2) << std::setfill(' ') << "" << " ";
		}
		std::cout << std::endl;
	}
}

#endif
