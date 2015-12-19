# Coconut

Coconut is an object-oriented runtime that adds Smalltalk-style objects and messaging features ; 
with a strong emphasis on concurrency ability and the subscripting side of things.

Coconut defines a base layer of classes fully integarted to C++, the data-structures hold ref-counted objects
and have a STL like interface regarding iterators and other common features. In addition to providing a set of useful primitive object classes, 
it introduces several paradigms that define functionality not covered by the C++ language. 


Coconut is designed with these goals in mind:

	- Provide a small set of basic utility classes.
	- Make software development easier by introducing consistent conventions.
	- Emphasizes on code readability, syntax allowing to express concepts in fewer lines of code.
	- Support Unicode strings and other legacy encodings, UTF-8, i18n and locale comparison, 
	- Support for path, filesystem and network access on different platforms.
	- Object persistence, object distribution, concurrency, multi-threadung, shared object, observer, looper.
	- Provide a level of OS independence, to enhance portability.



Coconut supports multiple programming paradigms, including object-oriented, imperative and 
functional programming or procedural styles, specifics such as the selector-key interface.
It features a dynamic type system and automatic memory management using scope ref-counting but without getting in the way, as you can work 
on the stack as well as on the heap ; you may copy and/or move, acquiring ref-counted containers on the fly.


Coconut is really similar to Smalltalk, Python, Swift Objective-C philosophy but purily written in C++.

# Few examples

```cpp
String str = u8"étourdie";
if (str == u8"étourdie") {
...
}

if (str < u8"Avion") {
...
}

...

str = u"étourdissement 나는태오";
std::cout << str.stringValue(); << std::endl;

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
	for (const auto & item : ref_cast<Array>(*values)) {
		std::cerr << "    + : " << item << std::endl;
	}
}

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