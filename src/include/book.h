/**
 * @file book.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * The book class is a class that contains a number of pages.  It manages retrieval of data from these pages, as well as updating them just-in-time and deleting them once their lifespan had expired.
 */

#ifndef BOOK_H
#define BOOK_H

/// The number of pages we store on a side (this is 2D paging, remember).
/// We actually store PAGE_COUNT*PAGE_COUNT pages, so this number should
/// not grow to large.
#define PAGE_COUNT 100

/// \brief Books contain pages and manage their interaction with the outside world.
///
/// Each book contains a large array of pages, which are created just-in-time and deleted when not needed anymore.
/// These pages are accessed when elements are requested from them, and any required computation is performed.
/// Once a page has outlived its age (defined in page.h) it is removed from memory, freeing up some space.
class book
{
	private:
		/// The pages are stored as a large 2D array of pointers.
		page* pages [PAGE_COUNT][PAGE_COUNT];
		/// Sometimes we wish to know how many pages are initialised
		int numberOfInitialisedPages;
	public:
		book();
		/// Returns the number of pages that are currently initialised and ready in memory.
		int getNumberOfInitialisedPages();
		/// Runs through all the pages, deleting those that are too old to matter much.
		void deleteUnused();
};


#endif 