Coconut
=======

Coconut is an object-oriented runtime, cross-platform, written in modern C++ that adds Smalltalk-style objects, dynamic typing and messaging features ; 
with a strong emphasis on concurrency ability, the subscripting side of things e.g `feel like scripting`, Coconut is more than just yet-another-Object 
framework: it adds a syntax within the syntax, close to a meta-programming approach (or embedded meta-language) what we named mainly Features.
Coconut implements type introspection (e.g knowing type [parent-type, properties] of an object at runtime) and a tiny barebones reflection system: 
a meta-object protocol (MOP).

-----------------------------------------------------------------------------------------------

Coconut defines a base layer of classes, fully integrated to the host-lang: C++, the data-structures hold ref-counted objects
and have a STL like interface regarding iterators, subscript operators, streams and other common features. In addition to providing a set of useful primitive object classes, 
it introduces several paradigms that define functionality not covered by the C++ language. 

-----------------------------------------------------------------------------------------------

Coconut is designed with these goals in mind:

- To offer a small set of basic utility classes optimized for use in a multi-threading environment.
- Performances and memory footprint in mind <sup>(1)</sup>.
- Exceptions are used as defects: we don't recover from any exception, we let the propagation happening <sup>(2)</sup>. 
- The internal implementation doesn't use any 'auto type constructs everything must stay explicit.
- Not only reserved to desktops but also distributed systems <sup>(3)</sup>.
- Concurrent block/lambda executions, concurrency, multi-threading, asynchronous dispatch, IPC.
- Traversable, iterable, sortable collections thru the KVC interface not relaying on binary comparison.
- Make software development easier by introducing consistent conventions.
- Code readability, syntax, allowing to express concepts in fewer lines of code.
- Support Unicode strings <sup>(4)</sup> and other legacy encodings, UTF-8, i18n and locale comparison. 
- Support for Path, Stream <sup>(5)</sup>, filesystem and network access on different platforms.
- Safe and transparent access to the main loop or UI loop queue of the platform e.g safely signaling the UI thread.
- Object persistence, distribution, melt-in KVO notifications, event looper.
- Provide a level of OS independence, to enhance portability <sup>(6)</sup>.

-----------------------------------------------------------------------------------------------

<sup>1 - The author has a background in embedded systems ; not in a limited sense of mobile software programming ; and real-time signal processing.</sup>

<sup>2 - It must crash, Zero Fault tolerance, exceptions these days are used in a cargo-cult way hidding ton of bugs because people tend to violate their own exception handling contract, we don't want that.

<sup>3 - The author knows about fail-over clusters and everything in between.</sup>

<sup>4 - By default width insensitive ; e.g composed or precomposed insensitive.</sup>

<sup>5 - UTF-16, UTF-8 agnostic parsing and conversion.</sup>

<sup>6 - Without the temptation of becoming a cargobay and only using a small set of selected dependencies.</sup>

-----------------------------------------------------------------------------------------------

Coconut supports multiple programming paradigms, including object-oriented, imperative and functional programming or procedural styles and 
other specifics such as the selector-key interface. It features a dynamic type system and automatic memory management using the built-in 
scope ref-counting system but without getting in the way, as you can work on the stack as well as on the heap ; you may copy and/or move, 
acquiring ref-counted containers on the fly. Coconut is really similar to Smalltalk, Ruby, Python, Swift and the Objective-C philosophy 
but purily written in modern-portable C++.

-----------------------------------------------------------------------------------------------

Coconut Objects sit between runtime (dynamic) and compile-time (static) polymorphism, however, 
we did not templatized collections (which are underneath templates containing Any Objects) like in Rust or Swift because it has no advantages 
in our configuration regarding performances over than making initialization trivial and breaking the self-reference design, hence useless.
Note that Coconut is written in C++11. C++14 is not widely and fully implemented yet.

-----------------------------------------------------------------------------------------------

Credits && builtin runtime dependencies:

- ASIO (Looper/Timer/Periodic/Events) http://think-async.com
- ICU (Unicode/Punycode/Localization) http://site.icu-project.org
- NLOHMANN JSON (Serialization) http://nlohmann.me, https://github.com/nlohmann/json
- PUGI XML (Serialization/DOM) http://zeuxcg.org, http://pugixml.org
- MBED TLS (SSL/TLS) <sup>(1)</sup> https://github.com/ARMmbed/mbedtls, https://www.mbed.com
- URIPARSER (RFC 3986) http://uriparser.sourceforge.net, https://www.ietf.org/rfc/rfc3986.txt

-----------------------------------------------------------------------------------------------

<sup>1 - We have an experimental unpublished yet frontent for ASIO, covering more than the actual OpenSSL bindings.</sup>

-----------------------------------------------------------------------------------------------

Forked and melted with significant changes:

- BASE64 (RFC 2045, Ryan Petrie) http://www.flipcode.com/archives/Base64_Encoder_Decoder.shtml, https://www.ietf.org/rfc/rfc2045.txt
- SHA1/SHA256 (Stephan Brumme) http://create.stephan-brumme.com/hash-library
- THREAD_POOL (Tyler Hardin) https://github.com/Tyler-Hardin/thread_pool

-----------------------------------------------------------------------------------------------

# Few examples

```cpp

// String, literal, locale and lexical comparison

String str = u8"étourdie";
if (str == u8"étourdie") {
...
}

if (str < u8"Avion") {
...
}

str = u"étourdissement 나는태오";
std::cout << str << std::endl;
//
// output: "étourdissement 나는태오"
//

String oUmlaut = u"\u00f6";
String oPlusUmlaut = u"o\u0308";

std::cout << "[ oUmlaut " << (oUmlaut.compare(oPlusUmlaut) == OrderedSame) << "] " << std::endl;
std::cout << "[ oUmlaut " << oUmlaut.localizedCompare(oPlusUmlaut) << "] " << std::endl;
std::cout << "[ oUmlaut == oPlusUmlaut " << (oUmlaut == oPlusUmlaut) << "] " << std::endl;
std::cout << "[ oUmlaut == oPlusUmlaut " << (oUmlaut == u"o\u0308") << "] " << std::endl;

```
```cpp

// Number to String

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

// Traversing collections by key-path.

MutableArray tree;
for (std::size_t i = 0; i < 10; i++ ) {
	auto child = With<Dictionary>({
		{ With<String>(u8"child"), With<Number>(i + 1) }
	});
	auto parent = With<Dictionary>({
		{ With<String>(u8"parent"), child }
	});
	tree + parent;
}

std::cerr << tree << std::endl;
//
// output: [{"parent": {"child": 1}}, {"parent": {"child": 2}}, {"parent": {"child": 3}}, {"parent": {"child": 4}}, {"parent": {"child": 5}}, {"parent": {"child": 6}}, {"parent": {"child": 7}}, {"parent": {"child": 8}}, {"parent": {"child": 9}}, {"parent": {"child": 10}}]
//

auto values = tree.valueForKeyPath(u8"parent.child");
if (KindOf<Array>(values)) {
	for (const auto & item : Thus<Array>(values)) {
		std::cerr << "    + : " << item << std::endl;
	}
}

```
```cpp

// Sorting nested collections

Array firstNames = {
	With<String>(u8"Alice"),
	With<String>(u8"Bob"),
	With<String>(u8"Charlie"),
	With<String>(u8"Quentin")
};

std::cerr << firstNames << std::endl;
//
// output: ["Alice", "Bob", "Charlie", "Quentin"]
//

Array lastNames = {
	With<String>(u8"Smith"),
	With<String>(u8"Jones"),
	With<String>(u8"Smith"),
	With<String>(u8"Alberts")
};

std::cerr << lastNames << std::endl;
//
// output: ["Smith", "Jones", "Smith", "Alberts"]
//

Array ages = {
	With<Number>(24),
	With<Number>(27),
	With<Number>(33),
	With<Number>(31)
};

std::cerr << ages << std::endl;
//
// output: [24, 27, 33, 31]
//

Array keys = {
	With<String>(u8"firstName"),
	With<String>(u8"lastName"),
	With<String>(u8"age")
};

std::cerr << keys << std::endl;
//
// output: ["firstName", "lastName", "age"]
//

```
```cpp

// Enumerating and aggregating

MutableArray people;

// Building an Array of Dictionary objects
firstNames.enumerateObjectsUsingFunction(
	[&lastNames, &ages, &keys, &people] (const Owning<Any> & obj, std::size_t index, bool & stop)
{
	// Creating, mapping an individual person
	auto person = With<Dictionary>({
		{ keys[0], obj },
		{ keys[1], lastNames[index] },
		{ keys[2], ages[index] }
	});
	// Adding person to people
	people + person;

}, EnumerationConcurrent);

// or

Enumerate<Array>(firstNames,
	[&lastNames, &ages, &keys, &people] (const Owning<Any> & obj, std::size_t index, bool & stop)
{
	people + With<Dictionary>({
		{ keys[0], obj },
		{ keys[1], lastNames[index] },
		{ keys[2], ages[index] }
	});
}, EnumerationConcurrent);

```
```cpp

// Traversing and sorting

SortDescriptor s0 {u8"firstName", false};
SortDescriptor s1 {u8"lastName", false};
SortDescriptor s2 = u8"age";

// Sorting on "lastName", "firstName" both descending.
auto sorted = people.sortedArrayUsingDescriptors({ &s1, &s0 });

std::cerr << sorted << std::endl;
//
// output: [{"age": 33, "firstName": "Charlie", "lastName": "Smith"}, {"age": 24, "firstName": "Alice", "lastName": "Smith"}, {"age": 27, "firstName": "Bob", "lastName": "Jones"}, {"age": 31, "firstName": "Quentin", "lastName": "Alberts"}]
//

```
```cpp

// Pythonic slicing like operator

std::cout << people[1] << std::endl;
std::cout << people[{ -1, 1, 2 }] << std::endl;

```
```cpp

// Javascriptic testing like syntax

bool test = people.someObjectPassingTest(
	[] (const Owning<Any> & obj, std::size_t index, bool & stop) -> bool
{
	if (/* ... condition */) {
		return true;
	}
	return false;
}, EnumerationConcurrent);

```
```cpp

// Unlike in Cocoa, collections are traversable by index-key-path : 
// read and write (if the destination object is mutable), mostly
// the coconut KVC interface is more advanced and complex. 

MutableArray tree;
for (std::size_t i = 0; i < 10; i++ ) {
	tree + With<Array>({
		With<Dictionary>({
			{ With<String>(u8"child"), With<Number>(i + 1) }
		})
	});
}

std::cerr << tree << std::endl;
//
// output: [[{"child": 1}], [{"child": 2}], [{"child": 3}], [{"child": 4}], [{"child": 5}], [{"child": 6}], [{"child": 7}], [{"child": 8}], [{"child": 9}], [{"child": 10}]]
//

tree.enumerateObjectsUsingFunction(
	[&tree] (const Owning<Any> & obj, std::size_t index, bool & stop)
{
	auto num = tree.valueForKeyPath(Number(index).stringValue() + u8".0.child");
	std::cerr << "+ index : " << index << "], valueForKeyPath : " << num << std::endl;
}, EnumerationConcurrent|EnumerationReverse);

```
```cpp

// Using selector key

Array list = {
	With<String>(u8"Banana"),
	With<String>(u8"Apple"),
	With<String>(u8"étourdie"),
	With<String>(u8"éa"),
	With<String>(u8"Cherry"),
	With<String>(u8"å"),
	With<String>(u8"Pear"),
	With<String>(u8"epic")
};

auto sorted = list.sortedArrayUsingSelectorKey(u8"@localizedCaseInsensitiveCompare:");

std::cerr << sorted << std::endl;
//
// output: ["å", "Apple", "Banana", "Cherry", "éa", "epic", "étourdie", "Pear"]
//

```
```cpp
// Coconut Easy Concurrent Jobs: similar to a Callable 
// in Java but purely lambda expressions driven :

auto job = JobExec(JobPolicyAsync, []() -> bool
{
	bool result = false;
	//
	// do something;
	// 
	return result;
});

// Acquiring. Note the function operator access.

bool whathappened = job();

//
// Shortcut asynchronous handler.
//

bool job = JobRun([]() -> bool
{
	bool result = false;
	//
	// do something;
	// 
	return result;
});

// continue...

//
// Using a thread pool to perform pseudo-parallel computations.
//

JobPool pool {4}; // spawning 4 Job-workers.

// Storing promise-results.

std::vector< JobReturn< std::pair<int, bool> > > tasks;

for (int i = 0; i < 10; i++) {
	// Note the function operator access.
	tasks.push_back(pool(
		[i] (int ii) -> std::pair<int, bool> {
			return std::make_pair(i * ii, (i * ii) % 2);
		}, i)
	);
}

// Acquiring.

for (auto i = tasks.begin(); i != tasks.end(); i++) {
	auto n = (*i)();
	std::cout << "+ is_odd : " <<  n.first << " -> " << std::boolalpha << n.second << std::endl;
}

```
```cpp

// STL bindings, Coconut collections (or data structures) already implement 
// those algorithms but adding concurrency options among other things 
// (ex: multiplexing/interleaving for mutable types) not covered by the STL 
// algorithm interfaces. Thus, just an explicit example to show the existing
// interoperability between both: end-user's choice, this is an inherent part
// of the Coconut's philosophy, hiding complexity but without getting in the
// way, when necessary.

auto names = firstNames + With<String>(u8"Alberts") + Number(44) + Date();

std::for_each(names.crbegin(), names.crend(),
	[] (const Owning<Any> & obj) -> void
{ std::cerr << " + name + : " << obj << std::endl; });

if (std::all_of(
	std::begin(names),
	std::end(names),
	[] (const Owning<Any> & obj) -> bool { return KindOf<Object>(obj); })
) {
	std::cerr << " + all of Anys are Objects in + : " << names << std::endl;
}

if (std::none_of(
	names.cbegin(),
	names.cend(),
	[] (const Owning<Any> & obj) -> bool { return MemberOf<Data>(obj); })
) {
	std::cerr << " + no Data in + : " << names << std::endl;
}

if (std::any_of(
	names.cbegin(),
	names.cend(),
	[] (const Owning<Any> & obj) -> bool { return MemberOf<Date>(obj); })
) {
	std::cerr << " + there is at least one Date in + : " << names << std::endl;
}

```