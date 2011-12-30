#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::left;

#include <iomanip>
using std::setw;

#include <cstdlib>
using std::rand;
using std::srand;
using std::malloc;

#include <ctime>
using std::time;

#include <queue>
using std::queue;

#define SIZE 100

void bucketsort(unsigned int *array, unsigned int size);

int main()
{
	unsigned int array[SIZE];
	unsigned int c;
	
	srand(time(nullptr));	// use current time in seconds as random seed
	
	for(c = 0 ; c < SIZE ; c++)	// randomize contents of array
		array[c] = rand() * rand();
	cout << "An array of " << SIZE << " random numbers:\n\n";
	for(c = 0 ; c < SIZE ; c++)	// display array (5 numbers per row)
	    cout << setw(15) << array[c] << ((c+1)%5 ? "" : "\n");
	cout << endl;
	
	//bucketsort(array, SIZE);	// sort array
	
	cout << "The same array sorted:\n\n";
	//for( c = 0 ; c < 5 ; c++ )	// print a header?
	//    cout << "     9876543210";
	cout << '|' << endl;
	for(c = 0 ; c < SIZE ; c++)	// display array (5 numbers per row)
	    cout << setw(15) << array[c] << ((c+1)%5 ? "" : "\n");
	cout << endl;
	
	system("PAUSE");
	return 0;
} // end function main


void bucketsort(unsigned int *current, unsigned int size)
{
	unsigned int *end;
	unsigned char *byte;
	queue<unsigned int> *upper;
	queue<unsigned int> *upperEnd;
	queue<unsigned int> *lower;
	queue<unsigned int> *lowerEnd;
	size_t digit;
	unsigned int number;
	void *temp;
	
	upper = new queue<unsigned int> [256];
	lower = new queue<unsigned int> [256];
	upperEnd = upper + 256;
	lowerEnd = lower + 256;
	
	end = current + size;
	byte = (unsigned char*)current;
	while(current < end)
	{
		upper[*byte].push(*current++);
		byte += sizeof(unsigned int);
	} // end while

//	//
//	while( upper < upperEnd )
//	{
//		while( !upper->empty() )
//		{
//			number = upper->front();
//			upper->pop();
//			cout << number << '\t';
//		}
//		cout << endl;
//		upper++;
//	}
//	upper = upperEnd - 256;
//	//
	digit = 0;
	while( ++digit < sizeof(unsigned int) )
	{
		byte = (unsigned char*)&number + digit;
		
		while( upper < upperEnd )
		{
			while( !upper->empty() )
			{
				number = upper->front();
				upper->pop();
				lower[*byte].push(number);
			}
			upper++;
		}
		upper = lower;
		lower = upperEnd - 256;
		temp = upperEnd;
		upperEnd = lowerEnd;
		lowerEnd = (queue<unsigned int> *)temp;
	} // end while
	
	free(lower);
	current = end - size;
	while( upper < upperEnd )
	{
		while( !upper->empty() )
		{
			*current++ = upper->front();
			upper->pop();
		}
		upper++;
	} // end while

	
//	c = 0;
//	while(current < end)
//		buckets[0].push(*current++);
//	while(!buckets[0].empty())
//	{
//		cout << buckets[0].front() << (++c%10 ? '\t' : '\n');
//		buckets[0].pop();
//	}
//	cout << endl;
	
} // end function bucketsort
