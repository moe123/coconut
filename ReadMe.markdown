Coconut
=======

Coconut is an object-oriented cross-platform runtime written in modern C++ that adds Smalltalk-style objects, dynamic typing and messaging features ; 
with a strong emphasis on concurrency ability and the subscripting side of things, `feel like scripting`.

-----------------------------------------------------------------------------------------------

Coconut defines a base layer of classes fully integrated to the host-lang: C++, the data-structures hold ref-counted objects
and have a STL like interface regarding iterators, subscript operators, streams and other common features. In addition to providing a set of useful primitive object classes, 
it introduces several paradigms that define functionality not covered by the C++ language. 

-----------------------------------------------------------------------------------------------

Coconut is designed with these goals in mind:

- Provide a small set of basic utility classes.
- Performances and memory footprint in mind (The author has a background in embedded systems and real-time signal processing).
- The internal implementation doesn't use any 'auto type constructs everything must stay explicit.
- Not only reserved to desktops but also distributed systems.
- Concurrent block/lambda executions, concurrency, multi-threading, asynchronous dispatch, IPC.
- Traversable, iterable, sortable collections thru the KVC interface not relaying on binary comparison.
- Make software development easier by introducing consistent conventions.
- Code readability, syntax, allowing to express concepts in fewer lines of code.
- Support Unicode strings (by default width insensitive ; e.g composed or precomposed) and other legacy encodings, UTF-8, i18n and locale comparison. 
- Support for Path, Stream (UTF-16, UTF-8 agnostic parsing and conversion), filesystem and network access on different platforms.
- Safe and transparent access to the main loop or UI loop queue of the platform e.g safely signaling the UI thread.
- Object persistence, distribution, melt-in KVO notifications, event looper.
- Provide a level of OS independence, to enhance portability.

-----------------------------------------------------------------------------------------------

Coconut supports multiple programming paradigms, including object-oriented, imperative and 
functional programming or procedural styles and other specifics such as the selector-key interface.
It features a dynamic type system and automatic memory management using the built-in scope ref-counting system but without getting in the way, as you can work 
on the stack as well as on the heap ; you may copy and/or move, acquiring ref-counted containers on the fly. 
Coconut is really similar to Smalltalk, Python, Swift and the Objective-C philosophy but purily written in modern-portable C++.

# Few examples

```cpp
String str = u8"étourdie";
if (str == u8"étourdie") {
...
}

// literal and lexical comparison

if (str < u8"Avion") {
...
}

...

str = u"étourdissement 나는태오";
std::cout << str.stringValue(); << std::endl;

// or simply

std::cout << str << std::endl;

String oUmlaut = u"\u00f6";
String oPlusUmlaut = u"o\u0308";

std::cout << "[ oUmlaut " << (oUmlaut.compare(oPlusUmlaut) == OrderedSame) << "] " << std::endl;
std::cout << "[ oUmlaut " << oUmlaut.localizedCompare(oPlusUmlaut) << "] " << std::endl;
std::cout << "[ oUmlaut == oPlusUmlaut " << (oUmlaut == oPlusUmlaut) << "] " << std::endl;
std::cout << "[ oUmlaut == oPlusUmlaut " << (oUmlaut == u"o\u0308") << "] " << std::endl;

```
```cpp

String s = u8"-15";

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
if (values && values->isKindOf(ArrayClass)) {
	for (const auto & item : Thus<Array>(values)) {
		std::cerr << "    + : " << item << std::endl;
	}
}

```
```cpp

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

const Array people_sort = people.sortedArrayUsingDescriptors({ &s1, &s0 });

for (Array::const_iterator it = people_sort.cbegin(); it != people_sort.cend(); ++it)
{
	std::cerr << " + people_sort: " << Thus<Dictionary>(*it).objectForKey(u8"firstName") << std::endl;
	std::cerr << " + people_sort: " << Thus<Dictionary>(*it).objectForKey(u8"lastName") << std::endl;
}

```
```cpp

// Pythonic

std::cout << people[1] << std::endl;
std::cout << people[{ -1, 1, 2 }] << std::endl;

```
```cpp

// Javascriptic

bool test = people.someObjectPassingTest(
	[] (const_kind_ptr & obj, std::size_t index, bool & stop) -> bool
{
	if (/* ... condition */) {
		return true;
	}
	return false;
}, EnumerationConcurrent);

```
```cpp

// Array, Set are traversable by index-key-path : 
// read and write (if the destination object is mutable).

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

for (std::size_t i = 0; i < 10; i++ ) {
	auto num = indexTree.valueForKeyPath(Number(i).stringValue() + u8".0.child");
	std::cerr << "    + : " << num << std::endl;
}

```
```cpp

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