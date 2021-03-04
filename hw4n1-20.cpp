#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <limits>
#include <array>

constexpr int integer_sqrt(int n) //rounded up
{
	int left = 1, right = n - 1;
	int middle = left + ((right - left) / 2);
	while (left != right)
	{
		middle = left + ((right - left) / 2);
		n / middle < middle ? right = middle : left = middle + 1;
	}
	return right;
}

int main()
{
	std::vector<int> v1(10U,0);
	std::iota(std::begin(v1), std::end(v1), 1); //#1-sequence of numbers

	std::copy(std::istream_iterator < int >(std::cin), std::istream_iterator < int >(),	std::back_inserter(v1)); //#2-some more numbers

	std::default_random_engine dre(std::chrono::system_clock().now().time_since_epoch().count());

	std::shuffle(std::begin(v1), std::end(v1), dre); //#3-mixing

	std::sort(std::begin(v1), std::end(v1));
	v1.erase(std::unique(std::begin(v1), std::end(v1)), std::end(v1)); //#4-deleting doubles

	auto odds = std::count_if(std::begin(v1), std::end(v1), [](auto x) {return x % 2; }); //#5-2n+1

	std::cout << "odds: " << odds << '\n';

	auto [min, max] = std::minmax_element(v1.begin(), v1.end()); //#6-min&max

	std::cout << "min: " << *min << ", max: " << *max << '\n';

	auto is_prime = [](auto x)
	{
		if (x == 2)
		{
			return true;
		}
		if (x < 2 || !(x % 2))
		{
			return false;
		}
		for (auto i = 3; i <= integer_sqrt(x); i += 2)
		{
			if (!(x % i))
			{
				return false;
			}
		}
		return true;
	};

	auto it = std::find_if(std::begin(v1), std::end(v1), is_prime);
	if (it != std::end(v1))
	{
		std::cout << "prime: " << *it << '\n';
	}//#7-search4simple

	std::for_each(std::begin(v1), std::end(v1), [](auto& x) {x = x * x; }); //#8-squares

	std::uniform_int_distribution <> uid(0, 1000);
	const std::size_t N = v1.size();
	std::vector<int> v2(N, 0);

	std::generate_n(std::begin(v2), N, [&dre, &uid]() {return uid(dre); }); //#9-2nd sequence

	auto sum = std::accumulate(std::begin(v2), std::end(v2), 0); //#10-summ

	std::fill_n(std::begin(v2), 4, 1); //#11-turn into 1

	std::vector<int> v3(N, 0);

	std::transform(std::begin(v1), std::end(v1), std::begin(v2), std::begin(v3), std::minus()); //#12-3d sequence

	std::replace_if(std::begin(v3), std::end(v3), [](auto x) {return x < 0; }, 0); //#13-turn into 0

	v3.erase(std::remove_if(std::begin(v3), std::end(v3), [](auto x) {return x == 0; }), std::end(v3)); //#14-deleting 0s

	std::reverse(std::begin(v3), std::end(v3)); //#15-reverse
	
	if (v3.size() > 2)
	{
		std::nth_element(std::begin(v3), std::prev(std::end(v3), 3), std::end(v3));
		std::cout << "top 3: ";
		std::copy(std::prev(std::end(v3), 3), std::end(v3), std::ostream_iterator < int >(std::cout, " "));
		std::cout << '\n';
	} //#16-top-3

	std::sort(std::begin(v1), std::end(v1));
	std::sort(std::begin(v2), std::end(v2)); //#17-from small to big

	std::vector <int> v4;
	std::sort(std::begin(v3), std::end(v3));
	std::merge(std::begin(v1), std::end(v1), std::begin(v3), std::end(v3), std::back_inserter(v4)); //#18-4th sequence

	std::sort(std::begin(v4), std::end(v4));
	auto range = std::equal_range(std::begin(v4), std::end(v4), 1); //#19-1 into 4th

	std::cout << "v1: ";
	std::copy(v1.cbegin(), v1.cend(), std::ostream_iterator < int >(std::cout, " "));
	std::cout << '\n';

	std::cout << "v2: ";
	std::copy(v2.cbegin(), v2.cend(), std::ostream_iterator < int >(std::cout, " "));
	std::cout << '\n';

	std::cout << "v3: ";
	std::copy(v3.cbegin(), v3.cend(), std::ostream_iterator < int >(std::cout, " "));
	std::cout << '\n';

	std::cout << "v4: ";
	std::copy(v4.cbegin(), v4.cend(), std::ostream_iterator < int >(std::cout, " "));
	std::cout << '\n'; //#20-output

	return 0;
}