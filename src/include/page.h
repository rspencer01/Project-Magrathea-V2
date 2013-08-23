/**
 * @file page.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * The page class holds a chunk of data.  This data can be operated on in various ways.  Pages are stored in books and are deleted if they get too old.
 */

#ifndef PAGE_H
#define PAGE_H

/// The size of the data that this page holds.  Since it is 2D, any page actually holds
/// PAGE_SIZE*PAGE_SIZE pieces of data.  Thus this should not get too large.
#define PAGE_SIZE 100

/// \brief Pages are contained in books and hold and perform operations on data.
///
/// Each page contains a large array of data which can be accessed at any time.
class Page
{
	private:
		int data[PAGE_SIZE][PAGE_SIZE];
	public:
		Page();
		/// Returns the value of the data indexed by the values (from the page origin)
		int getAt(int,int);
		/// Returns whether or not the page should be deleted
		bool toBeDeleted();
};

#endif
