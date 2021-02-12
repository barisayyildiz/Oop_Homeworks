#ifndef EXC
#define EXC


namespace excNamespace
{
	class InvalidInput : public std::exception
	{
		public:
			const char *what()const throw()
			{
				return "Invalid input";
			}

	};

	class InvalidSize : public std::exception
	{
		public:
			const char *what()const throw()
			{
				return "Size should be greater than 5";
			}
	};

	class FileError : public std::exception
	{
		public:
			const char *what()const throw()
			{
				return "No such file exists";
			}
	};

	class IndexError : public std::exception
	{
		public:
			const char *what()const throw()
			{
				return "Wrong Index Number";
			}
	};

	class UndoError : public std::exception
	{
		public:
			const char *what()const throw()
			{
				return "Cannot undo more...";
			}
	};

	class AllocatedCell : public std::exception
	{
		public:
			const char *what()const throw()
			{
				return "Cell is already allocated";
			}
	};

	class CounterZero : public std::exception
	{
		public:
			const char *what()const throw()
			{
				return "Counter is 0, cannot get last move";
			}

	};


}

#endif

