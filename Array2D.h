#ifndef _ARRAY_2D_H_
#define _ARRAY_2D_H_

#include <vector>
#include <stdexcept>

/**
 * A class that represents a jagged 2D array of items.
 */
template <class T>
class Array2D
{
private:
	std::vector<std::vector<T> > _arr;
	size_t _bigSize;
	std::vector<size_t> _smallSizes;
	const float RESIZE_FACTOR = 1.5f;
public:
	Array2D() : _bigSize(0) {}

	void addItem(T item, unsigned bigIndex, unsigned smallIndex)
	{
		if (bigIndex >= _bigSize)
		{
			_bigSize = RESIZE_FACTOR * (bigIndex + 1);
			_arr.resize(_bigSize);
			_smallSizes.resize(_bigSize, 0);
		}
		if (smallIndex >= _smallSizes[bigIndex])
		{
			_smallSizes[bigIndex] = RESIZE_FACTOR * (smallIndex + 1);
			_arr[bigIndex].resize(_smallSizes[bigIndex], nullptr);
		}
		_arr[bigIndex][smallIndex] = item;
	}

	inline unsigned getNumRows() const
	{
		return _bigSize;
	}

	inline unsigned getNumItems(unsigned bigIndex) const
	{
		if (bigIndex < _bigSize)
		{
			return _smallSizes[bigIndex];
		}
		else
		{
			throw std::invalid_argument("bigIndex is out of bounds.");
		}
	}

	inline T getItem(unsigned bigIndex, unsigned smallIndex) const
	{
		if (bigIndex < _bigSize)
		{
			return _arr[bigIndex][smallIndex];
		}
		else
		{
			throw std::invalid_argument("bigIndex is out of bounds.");
		}
	}

	void clearItems(unsigned bigIndex)
	{
		if (bigIndex < _bigSize)
		{
			_arr[bigIndex].clear();
			_smallSizes[bigIndex] = 0;
		}
		else
		{
			throw std::invalid_argument("bigIndex is out of bounds.");
		}
	}
};

#endif