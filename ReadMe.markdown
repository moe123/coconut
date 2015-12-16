# Coconut

![Alt text](https://raw.githubusercontent.com/cucurbita/coconut/master/ReadMe/pure.png)

An Object Runtime a la SmallTalk/Obj-C (Apple Foundation like) on top of C++ (11), 
no 14 even if we are interested in many new nifty things. Coconut is not yet another 
Object rooted framework, but a runtime-object hosted in C++, it aims to address complex and 
challenging OOP and software features exposed in a simple manner ; e.g Object subscripting in C++.

We follow cocoa as a layout, but this is a free interpretation, 
we are keeping what we like and ignore some parts, such as the 
key-value-coding-as-is, the notification-observer-model, we'll go on a queue async dispatch model pretty 
much like a network client-server model. As well as, we don't hesitate borrowing good stuff from other rt-objects such as Java, 
Lua, Python and surely SmallTalk. We separated String and Path for OOP concerns and 
also performances, the Path class needs less options and does not weigh down the String class which 
is made for unicode-text representations.

We kept the Mutable and Immutable side of things 
but in extending objects (means class inheritance, you don't pay the price of mutability if 
you don't want to, most of the time, in a program, objects used are immutable, plus, we take advantages 
from the host-lang, weak pointers, shared pointers, stack references, iterator facades and so on) ; 
Mutable objects are thread-safe one-writer many readers, 
we are also introducing new-object kinds and therefore serializable.

Note about collections:
- None Object represents a Null invalid value or simply null-error.
- Empty Object represents a Null valid value, e.g do not store None Object.
- By default collections increase the ref-count of objects when inserted.
- Copy, kindCopy, mutableCopy perform a real data copy e.g see CopyOption.
- If a CopyOption is set all the Objects are recursively copied ; leaves included.
- Collections are recursively traversable by key-path read and write, including arrays by key index.
- Collections do not relay on a hazardous binary compare, hashing, we have some time complexity ; but nothing terrible 
and not more than binary comparison, just look up calls tiny overhead, which is corrected by concurrency, anyway it is 
possible to store Objects in a regular hashtable as they all have a hash value representation accessor.

Emphasis:

- performances and memory footprint in mind.
- hiding the complexity of various platforms.
- hiding the complexity of software.
- hiding in some ways the complexity of C++.
- UTF-8 representation of std::string
- unicode and i18n built-in, sorting, locale.
- concurrent block/lambda executions.
- traversable collections, serialization.
- melt-in observer-observing notifications.
- multi-threading and shared data without seeing it.
- not only reserved to desktop but also distributed sys.
- facilitating software development.
- building many other frameworks on top.
- non intrusive, coexist with other frameworks.
- runtime built-in dependencies hidden, no symbol collision.

#### SDK build

```sh

# Assuming export ISYSROOT="-isysroot /Applications/Xcode.app/Contents/Developer/\
# Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk  -mmacosx-version-min=10.10"
#
# If you need the profiler e.g debug symbols, just add -g to CFLAGS, 
# might be useful to remove hidden flags too.

# CFLAGS="${ISYSROOT} -std=c11 -arch x86_64 -fvisibility=hidden" \
# CXXFLAGS="${CFLAGS} -std=c++11 -fvisibility-inlines-hidden -stdlib=libc++" \
# CC="clang" CXX="clang++" ./configure

# ICU configure (55.1)
$ ./configure --prefix=/tmp/build/icu_build --enable-static --disable-shared --with-data-packaging=static

# URIPARSER configure (0.8.1)
$ ./configure --prefix=/tmp/build/uriparser_build --disable-wchar_t --enable-shared=no --disable-test --disable-doc

```

#### Examples

```cpp

// KVC and Object Representation notes:
	
	// Unlike in cocoa collection operators are part of the root Object.
	// Divide-and-conquer with reduction:
	/**
		kind_ptr sum(const std::string & utf8_key) const;
		kind_ptr min(const std::string & utf8_key) const;
		kind_ptr max(const std::string & utf8_key) const;
		kind_ptr avg(const std::string & utf8_key) const;

		kind_ptr distinctUnionOfObjects(const std::string & utf8_key) const;
		kind_ptr unionOfObjects(const std::string & utf8_key) const;	
		kind_ptr distinctUnionOfArrays(const std::string & utf8_key) const;		
		kind_ptr distinctUnionOfOrderedSets(const std::string & utf8_key) const;		
		kind_ptr distinctUnionOfSets(const std::string & utf8_key) const;	
		kind_ptr unionOfArrays(const std::string & utf8_key) const;		
		kind_ptr unionOfOrderedSets(const std::string & utf8_key) const;	
		kind_ptr unionOfSets(const std::string & utf8_key) const;
	**/

	// Unlike in cocoa every Object has numeric and string representation accessors.
	/**
		const std::string description() const;
		std::string stringValue() const; // guaranteed UTF-8 or plain ASCII
		std::u16string string16Value() const;
		std::u32string string32Value() const;

		float floatValue() const;
		double doubleValue() const;
		long double longDoubleValue() const;

		bool boolValue() const;
		char charValue() const;

		short shortValue() const;
		int intValue() const;
		long longValue() const;
		long long longLongValue() const;

		unsigned char unsignedCharValue() const;
		unsigned short unsignedShortValue() const;
		unsigned int unsignedIntValue() const;
		unsigned long unsignedLongValue() const;
		unsigned long long unsignedLongLongValue() const;
	**/

```

```cpp
	// Unicode String and literals

	String str = u8"étourdie";
	if (str == u8"étourdie") {
		...
	}
	
	// lexical and literal unicode comparison
	if (str < u8"Avion") {
		...
	}

	...
	
	str = u"étourdissement 나는태오";
	
	// UTF8 std::string
	std::cout << str.stringValue(); << std::endl;

	// UTF16 std::u16string (host byte-order)
	std::cout << str.string16Value(); << std::endl;
	
	// By default unicode is compared to whatever the form e.g SVU, 
	// this is the "text which matters ; not the geek side of things"

	String oUmlaut = u"\u00f6"; // o-umlaut
	String oPlusUmlaut = u"o\u0308";

	std::cout << "[ oUmlaut " << (oUmlaut.compare(oPlusUmlaut) == OrderedSame) << "] " << std::endl;
	std::cout << "[ oUmlaut " << oUmlaut.localizedCompare(oPlusUmlaut) << "] " << std::endl;
	std::cout << "[ oUmlaut == oPlusUmlaut " << (oUmlaut == oPlusUmlaut) << "] " << std::endl;
	std::cout << "[ oUmlaut == oPlusUmlaut " << (oUmlaut == u"o\u0308") << "] " << std::endl;

```

```cpp

// Number 2 String, literal, POD and vice-versa 

	String s(u8"-15");

	Number x(s.intValue());
	String y(x.stringValue());
	Number z(y.intValue());

// works too!
	Number x1 = s.intValue();
	String y1 = x1.stringValue();
	Number z1 = y1.intValue();

	Number n = 1U;
	n = 429496788;
	n = 26156.429496788;
	n = -26156.42f;

	Number n0 = 10;
	Number n1 = 5;

	std::cerr << " (n0 > n1) = " << (n0 > n1) << std::endl;

```	

```cpp
	...
	// main concept: collections hold ref-counted pointers ;
    // you can move from stack refs to pointers transparently.

	MutableArray tree;
	for (std::size_t i = 0; i < 10; i++ ) {
		auto child = Dictionary::with({
			{ String::with(u8"child"), Number::with(i + 1) }
		});
		auto parent = Dictionary::with({
			{ String::with(u8"parent"), child }
		});
		tree.addObject(parent);
	}
	auto values = tree.valueForKeyPath(u8"parent.child");
	// receiving a kind_ptr
	if (values && values->isKindOf(ArrayClass)) { // guarding dyn-identity
		// collections have built-in iterator-facades
		for (const auto & item : ref_cast<Array>(*values)) {
			// you can print Objects!
			std::cerr << "    + : " << item << std::endl;
		}
	}
	
	// collections are not copying by default ; just incrementing the refs-count @see CopyOption
	MutableArrayPtr tree_to_be_sent_to_other_thread = MutableArray::with(tree);
	MutableArrayPtr tree_to_be_sent_to_other_thread = MutableArray::with(tree.begin(), tree.end());
	
	...

// collections are subscriptable as well!

	MutableArray indexTree1;

	indexTree1[0] = Date::with();
	indexTree1[1] = String::with(u8"étourdie");

	...
```	

```cpp
	MutableArray indexTree;
	for (std::size_t i = 0; i < 10; i++ ) {
		auto child = Dictionary::with({
			{ String::with(u8"child"), Number::with(i + 1) }
		});
		auto parent = Array::with({
			child
		});
		indexTree.addObject(parent);
	}

	// KVC Unlike in cocoa collections are traversable by key-index
	// key-path: 
	//    [indexTree{Array, size=10}].
	//    [parent{Array, size=1}].
	//    [Dictionary['child'] => Number]
	
	for (std::size_t i = 0; i < 10; i++ ) {
		auto num = indexTree.valueForKeyPath(Number(i).stringValue() + u8".0.child");
		std::cerr << "    + : " << num << std::endl;
	}
	
```	

```cpp
	
	// KVC cocoa + coconut behaviors
	
	// indexTree = {};
	indexTree.removeAllObjects();
	for (std::size_t i = 0; i < 10; i++ ) {
		auto child = Dictionary::with({
			{ String::with(u8"child"), Number::with(i + 1) }
		});
		auto parent = Array::with({
			child,
			child,
			child
		});
		indexTree.addObject(parent);
	}
	
	for (std::size_t i = 0; i < 10; i++ ) {
		auto v = indexTree.valueForKeyPath(Number(i).stringValue() + u8".child");
		if (v && v->isKindOf(ArrayClass)) {
			std::cerr << "    +-+ : " << i << std::endl;
			for (std::size_t j = 0; j < v->size(); j++ ) {
				std::cerr << "      + : [" << j <<  "] " << *(ref_cast<Array>(*v)[j]) << std::endl;
			}
		}
	}
	
```

```cpp

// Unicode Sorting e.g selector key

	Array list = {
		String::with(u8"Banana"),
		String::with(u8"Apple"),
		String::with(u8"étourdie"),
		String::with(u8"éa"),
		String::with(u8"Cherry"),
		String::with(u8"å"),
		String::with(u8"Pear"),
		String::with(u8"epic")
	};
	
	Array sorted = list.sortedArrayUsingSelectorKey(u8"@localizedCaseInsensitiveCompare:");
	for (const auto & str : sorted) {
		std::cerr << "    + : " << str << std::endl;
	}

```

```cpp

// Traversing and Unicode Sorting e.g SortDescriptor

	...
	
	Array firstNames = {
		String::with(u8"Alice"),
		String::with(u8"Bob"),
		String::with(u8"Charlie"),
		String::with(u8"Quentin")
	};
	
	Array lastNames = {
		String::with(u8"Smith"),
		String::with(u8"Jones"),
		String::with(u8"Smith"),
		String::with(u8"Alberts")
	};
	
	Array ages = {
		Number::with(24),
		Number::with(27),
		Number::with(33),
		Number::with(31)
	};
	
	Array keys = {
		String::with(u8"firstName"),
		String::with(u8"lastName"),
		String::with(u8"age")
	};
	
	MutableArray people;
	
	firstNames.enumerateObjectsUsingFunction(
		[&lastNames, &ages, &keys, &people] (const_kind_ptr & obj, std::size_t index, bool & stop)
	{
		people.addObject(
			Dictionary::with({
				{ keys[0], obj },
				{ keys[1], lastNames[index] },
				{ keys[2], ages[index] }
			})
		);
	}, EnumerationConcurrent);
	
	
	SortDescriptor s0(u8"firstName", false);
	SortDescriptor s1(u8"lastName", false);
	SortDescriptor s2(u8"age");
	
	Array people_sort = people.sortedArrayUsingDescriptors({ &s1, &s0 });
	
	for (Array::const_iterator it = people_sort.cbegin(); it != people_sort.cend(); ++it)
	{
		std::cerr << " + people_sort: " << ptr_cast<Dictionary>(*it)->objectForKey(u8"firstName") << std::endl;
		std::cerr << " + people_sort: " << ptr_cast<Dictionary>(*it)->objectForKey(u8"lastName") << std::endl;
	}

```

```cpp

// Enumerating, Selector key, concurrency

	people.performSelectorKeyAfterDelay(10000, false, u8"@isEqual:", people.copy());

	std::size_t idx = people.indexOfObjectPassingTest(
		[&n1] (const_kind_ptr & obj, std::size_t index, bool & stop) -> bool
	{
		if (obj && obj->isEqual(n1)) {
			std::cerr << "indexOfObjectPassingTest idx : " << index << " " <<  obj << std::this_thread::get_id() << std::endl;
			return true;
		}
		return false;
	}, EnumerationConcurrent);
	
	// nested concurrent blocks	
	JobDetach([]() -> void
	{
		auto job_1 = JobExec(JobPolicyAsync, []() -> bool
		{
			int i = 3000000;
			while(i--);
			std::cerr << "+ job_1 " << std::endl;
			return true;
		});
		bool res_1 = false;
		auto job_2 = JobExec(JobPolicyDeferred, [&job_1, &res_1]() -> bool
		{
			std::cerr << "+ job_2 " << std::endl;
			res_1 = job_1.get();
			return true;
		});
		
		bool res_2 = job_2.get();
		
		std::cerr << "+ res_1 " << res_1 << std::endl;
		std::cerr << "+ res_2 " << res_2 << std::endl;
		return;
	});

```

```cpp
// Unicode formatting
	String str = u"étourdissement 나는태오";
	String str_fmt = String::format
	(
		u"%S %llu %g %s %S %d %g %s %S \ub098\ub294\ud0dc\uc624 %llu %g",
		str.string16Value().c_str(),
		34555555,
		0.5666666,
		u8"étourdie",
		u"étourdie 나는태오",
		399555,
		0.5666666,
		u8"étourdie",
		u"나는태오",
		388555555,
		0.5666666
	);
	
	std::cerr << " + " << str_fmt << std::endl;
	
```

Not committed parts in progress as the rest of it:
		
		+ Async I/O dispatch, notification, observer, timer
			based on ASIO non-boost + a per system main-loop / UI-loop bind
				
		+ Unicode ~~String;Path;URL~~, Locale, TimeZone, ~~Charset/Encoding convertion~~ 
			based on ICU + a per system current-user-locale-timezone / UI-NonUI bind
		
		+ Network, Stream, Socket
			based on ASIO non-boost, BSD socket, Libcurl / OpenSSL (we would like 
			very much to get rid of it but it is not possible at this time)
			
		+ ~~Serialization~~
			based on pugixml, rapidjson, homebrew
			
		+ Sum up static private deps.
			
			- ICU standalone
			- URIParser
			- ASIO non-boost
			- pugixml, rapidjson
			- Libcurl / OpenSSL
			- Internal cooking / system and deps bindings
			- SQLite 
		
		+ The internal representation of std::string is guaranteed to be utf-8 or ascii 
		  with a transparent brige to std*stream familly to accept utf-8 or utf-16
		  file-paths. 
		
The main goal is to be cross-platform using a limited set of deps that are cross-platform, solid  
and easy to build, using non-commercial and non restrictive licenses ; all the platform specifics (2) 
and the bind to the deps happen in the runtime which can be built standalone.

2- e.g the crap.

proprietary ancestor (author too, among many other things, runs on embedded env too, and has better (a lot) perfomances in term of memory and execution than Obj-C) :

![Alt text](https://raw.githubusercontent.com/cucurbita/coconut/master/ReadMe/orig.png)

#