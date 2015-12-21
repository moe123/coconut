//
// coconut_test.cpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <other/coconut_test_attrs.hpp>

using namespace coconut;

COCONUT_SECTION_INI
{
	std::cerr << " _init " << std::endl;
}

COCONUT_SECTION_FINI
{
	std::cerr << " _fini " << std::endl;
}

const Owning<Any> operator "" _U(const char * in, std::size_t sz)
{ return String::with(in); }
	
const Owning<Any> operator "" _U(const char16_t * in, std::size_t sz)
{ return String::with(in); }
	
const Owning<Any> operator "" _U(long double in)
{ return Number::with(in); }
	
const Owning<Any> operator "" _U(unsigned long long in)
{ return Number::with(in); }
	
static void print_ref(const Any & ref)
{
	auto array = With<Array>
	({
		With<String>(u8"hello"),
		With<Number>(10),
		With<Number>(10.8),
		With<Date>()
	});
	
	std::cerr.setf(std::ios::fixed, std::ios::floatfield);
	std::cerr.precision(10);
	
	std::cerr << "+ description() : " << ref.description() << std::endl;
	std::cerr << "+ className() : " << ref.className() << std::endl;
	std::cerr << "+ classTree() : " << ref.classTree() << std::endl;
	
	//std::cerr << ref << std::endl;
	std::cerr << "+ stringValue() : " << ref.stringValue() << std::endl;
	
	std::cerr << "+ floatValue() : " << ref.floatValue() << std::endl;
	std::cerr << "+ doubleValue() : " << ref.doubleValue() << std::endl;
	std::cerr << "+ longDoubleValue() : " << ref.longDoubleValue() << std::endl;
	std::cerr << "+ boolValue() : " << ref.boolValue() << std::endl;
	std::cerr << "+ charValue() : " << static_cast<short>(ref.charValue()) << std::endl;
	std::cerr << "+ shortValue() : " << ref.shortValue() << std::endl;
	std::cerr << "+ intValue() : " << ref.intValue() << std::endl;
	std::cerr << "+ longValue() : " << ref.longValue() << std::endl;
	std::cerr << "+ longLongValue() : " << ref.longLongValue() << std::endl;
	std::cerr << "+ unsignedCharValue() : " << static_cast<unsigned short>(ref.unsignedCharValue()) << std::endl;
	std::cerr << "+ unsignedShortValue() : " << ref.unsignedShortValue() << std::endl;
	std::cerr << "+ unsignedIntValue() : " << ref.unsignedIntValue() << std::endl;
	std::cerr << "+ unsignedLongValue() : " << ref.unsignedLongValue() << std::endl;
	std::cerr << "+ unsignedLongLongValue() : " << ref.unsignedLongLongValue() << std::endl;
	
	std::cerr << "+ ---- + " << std::endl;
}

static void print_number(const Number & n)
{
	print_ref(n);
	std::cerr << "+ type() : " << n.type() << std::endl;
}

static void test_number(void)
{
	Number n = 1U;
	
	print_number(n);
	
	n = 429496788;
	
	print_number(n);
	
	n = 26156.429496788;
	
	print_number(n);
	
	n = -26156.42f;
	
	print_number(n);
}

static void print_array(const Array & a)
{
	// unlike in cocoa ; every Object can be accessed by value-representation blindly
	print_ref(a);
	for (const auto & item : a) {
		std::cerr << "    + : " << item << std::endl;
	}
	
	std::cerr << "+ ---- + " << std::endl;
	Owning<Any> item;
	std::size_t idx = 0;
	
	for (idx = 0 ; idx < a.size() ; ++idx) {
		item = a.objectAtIndex(idx);
		std::cerr << "+ objectAtIndex(" << idx << ")" << std::endl;
		if (item) { print_ref(*(a[idx])); }
	}
	if (idx > 0) {
		idx--;
		// unlike in cocoa Array(s) can be traversed by key-indexes,
		// if the key is not an unsigned integer, then same rules than in cocoa *.
		item = a.valueForKey(Number(idx).stringValue()); // Number
		std::cerr << "+ valueForKey(\"" << idx << "\") : " << item << std::endl;
		
		std::string key = String(u8"an unicøde ßtring").stringValue(); // UTF-8
		std::u16string key16 = String(u8"an unicøde ßtring").string16Value(); // UTF-16+BOM
		item = a.valueForKey(key);
		
		std::cerr << "+ valueForKey(\"" << key << "\") : " << item << std::endl; // array of nones
	}

#ifdef ZERO
	// + chaining dict.array.dict:
	d.valueForKeyPath(u8"unicøde.3.ßtring");
	
	// + chaining dict.array.dict.mutable_array:
	auto sz = d.valueForKeyPath(u8"unicøde.3.ßtring.@size");
	if(sz && sz->unsignedLongValue() > 5UL) {
		d.setValueForKeyPath(u8"unicøde.3.ßtring.5", ...);
	}
	
	// or
	auto arr = d.valueForKeyPath(u8"unicøde.3.ßtring");
	if(arr && arr->isKindOf(MutableArrayClass)) {
		if(ref_cast<MutableArray>(*arr).size() > 5) {
			d.setValueForKeyPath(u8"unicøde.3.ßtring.5", ...);
		}
	}
	
	// or
	auto arr = d.valueForKeyPath(u8"unicøde.3.ßtring");
	if(arr && arr->isKindOf(MutableArrayClass)) {
		if(ref_cast<MutableArray>(*arr).size() > 5UL) {
			ref_cast<MutableArray>(*arr).replaceObjectAtIndex(
				5,
				String::with(u8"an unicøde ßtring")
			);
		}
	}
	
	// or
	Owning<MutableArray> arr = ptr_cast<MutableArray>(
		d.valueForKeyPath(u8"unicøde.3.ßtring")
	);
	if(arr && arr->size() > 5) {
		arr->replaceObjectAtIndex(5, String::with(u8"an unicøde ßtring"));
	}
#endif
	 
}

static void test_array(void)
{
	Number n0 = 0U;
	Number n1 = 1U;
	Number n2 = 2U;
	Number n3 = 3U;
	Number n4 = 4U;
	Number n5 = 5U;
	Number n6 = 6U;
	Number n7 = 7U;
	Number n8 = 8U;
	
	Array a =
	{
		&n0,
		&n1,
		&n2,
		&n3,
		&n4,
		&n5,
		&n6,
		&n7,
		&n8,
		&n3,
		&n4,
		&n5,
		&n6,
		&n7,
		&n8
	};
	
	Array unique = a.uniquedArray();
	
	for (Array::const_iterator it = unique.cbegin(); it != unique.cend(); ++it)
	{
		std::cerr << " + unique: " << (*it) << std::endl;
	}
	
	Array shuffled = a.shuffledArray();
	
	for (Array::const_iterator it = shuffled.cbegin(); it != shuffled.cend(); ++it)
	{
		std::cerr << " + shuffled: " << (*it) << std::endl;
	}
	
	//return;
	
	a.performSelectorKeyAfterDelay(10000, false, u8"@isEqual:", None::with());
	
	std::size_t i = 8000000;
	
	while(i > 1) {
		i--;
	}
	
	std::size_t idx = a.indexOfObjectPassingTest([] (const Owning<Any> & obj, std::size_t index, bool & stop) -> bool {
		if (obj && obj->unsignedIntValue() > 2U) {
			return true;
		}
		return false;
	});
	
	std::cerr << "indexOfObjectPassingTest idx : " << idx << std::endl;
	
	std::cerr << "main this_thread  : " << std::this_thread::get_id() << std::endl;
	
	idx = a.indexOfObjectPassingTest([&n1] (const Owning<Any> & obj, std::size_t index, bool & stop) -> bool {
		if (obj && obj->isEqual(n1)) {
			std::cerr << "indexOfObjectPassingTest idx : " << index << " " <<  obj << std::this_thread::get_id() << std::endl;
			return true;
		}
		return false;
	}, EnumerationConcurrent);
	
	//std::this_thread::sleep_for(std::chrono::microseconds(500));
	
	std::cerr << "indexOfObjectPassingTest idx : " << idx << std::endl;

	
	Owning<Array> aa = Array::with
	({
		a[0], // increasing ref count &n0 [a copied]
		a[1], // increasing ref count  &n1 [a copied]
		a[2] // increasing ref count &n2 [a copied]
	});
	
	print_array(a);
	
	Owning<Array> b = Array::with(a, CopyKind);
	
	Owning<Array> bb = Array::with
	(
		b->begin(),
		b->end(),
		CopyMutable
	);
	
	print_array(*b);
	
	Owning<Number> n00 = Number::with(1L);
	Owning<Any> n11 = Number::with(4U);
	Owning<Number> n22 = Number::with(-3L);
	auto n33 = Number::with(n2);
	
	Array c = { n00, n11, n22, n33 };
	
	print_array(c);

	auto c1 = c.sortedArrayAscending();
	
	if (c1.isKindOf(ArrayClass)) {
		print_array(ref_cast<Array>(c1));
	}
	
	auto c2 = c.sortedArrayAscending();
	
	print_array(c2);
	
	Array c3 = c.sortedArrayDescending(CopyKind);
	
	print_array(c3);
}

static void test_date(void)
{
	using namespace coconut::runtime::algorithm;
	
	std::vector< std::pair<std::string, TimeInterval> > tms;
	
	tms.push_back(std::make_pair("TimeUnitPlainSeconds ", Date::timestamp(TimeUnitPlainSeconds, TimestampSinceJanuary1970)));
	tms.push_back(std::make_pair("TimeUnitDoubleSeconds", Date::timestamp(TimeUnitDoubleSeconds, TimestampSinceJanuary1970)));
	tms.push_back(std::make_pair("TimeUnitMilliSeconds ", Date::timestamp(TimeUnitMilliSeconds, TimestampSinceJanuary1970)));
	tms.push_back(std::make_pair("TimeUnitMicroSeconds ", Date::timestamp(TimeUnitMicroSeconds, TimestampSinceJanuary1970)));
	tms.push_back(std::make_pair("TimeUnitNanoSeconds  ", Date::timestamp(TimeUnitNanoSeconds, TimestampSinceJanuary1970)));
	
	for (auto && tm : tms) {
		std::cerr << "+ now_unixepoch ('" << tm.first << "') : " << to_string<std::string>(tm.second, 3) << std::endl;
	}
	
	tms.clear();
	
	tms.push_back(std::make_pair("TimeUnitPlainSeconds ", Date::timestamp(TimeUnitPlainSeconds, TimestampSinceReferenceDate)));
	tms.push_back(std::make_pair("TimeUnitDoubleSeconds", Date::timestamp(TimeUnitDoubleSeconds, TimestampSinceReferenceDate)));
	tms.push_back(std::make_pair("TimeUnitMilliSeconds ", Date::timestamp(TimeUnitMilliSeconds, TimestampSinceReferenceDate)));
	tms.push_back(std::make_pair("TimeUnitMicroSeconds ", Date::timestamp(TimeUnitMicroSeconds, TimestampSinceReferenceDate)));
	tms.push_back(std::make_pair("TimeUnitNanoSeconds  ", Date::timestamp(TimeUnitNanoSeconds, TimestampSinceReferenceDate)));
	
	for (auto && tm : tms) {
		std::cerr << "+ now_refepoch  ('" << tm.first << "') : " << to_string<std::string>(tm.second, 3) << std::endl;
	}
	
	tms.clear();
	
	Date dt;
	
	std::cerr << dt.stringValue() << std::endl;
	
	Date dt1 = Date::fromUTC(dt.stringValue());
	
	std::cerr << dt1.stringValue() << std::endl;
	
	
}
	
static void test_stuff(void)
{
	
	using namespace coconut::runtime;
	using namespace coconut::runtime::algorithm;
	
	Number n0 = 10;
	Number n1 = 5;
	
	std::cerr << " (n0 > n1) = " << (n0 > n1) << std::endl;
	
	String now = Date::UTC();
	std::cerr << " now = " << now << std::endl;
	
	Path path = u8"/usr/bin";
	
	std::cerr << " path = " << path << std::endl;
	
	URL url = u8"/usr/bin";
	
	std::cerr << " url = " << url << std::endl;
	
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
	if (values && values->isMemberOf(Array{})) {
		for (const auto & number : Thus<Array>(values)) {
			std::cerr << " number  + : " << number << std::endl;
		}
	}
	MutableArray indexTree;
	
	ref_cast<MutableArray>(indexTree);
	
	for (std::size_t i = 0; i < 10; i++ ) {
		auto child = Dictionary::with({
			{ String::with(u8"child"), Number::with(i + 1) }
		});
		auto parent = Array::with({
			child
		});
		indexTree.addObject(parent);
	}
	
	// Passing from Number 2 String
	
	String s(u8"\t\n 15,000AAD 6788");
	
	std::cerr << "  s.intValue()  + : " << s.doubleValue() << std::endl;
	
	Number x(s.intValue());
	String y(x.stringValue());
	Number z(y.intValue());
	
	std::string ty = u8"étourdie";
	
	String str0(u8"étourdie");
	
	String str1 = u8"étourdie";
	
	if (str0 == u8"étourdie") {
		std::cerr << u8" étourdie == " << str0 << " " << str0[0] << std::endl;
	}
	
	// unlike in cocoa collections are traversable by key index
	// key-path: [Array{indexTree, size=10}].[Array{parent, size=1}].Number
	
	for (std::size_t i = 0; i < 10; i++ ) {
		auto num = indexTree.valueForKeyPath(Number(i).stringValue() + u8".0.child");
		std::cerr << "    + : " << num << std::endl;
	}
	
	// out of bounds capacity, seeing index as key-like,
	// subscripting, script language
	// to use with moderation
	
	indexTree[10] = String::with(u8"étourdie");
	indexTree[40] = Date::with();
	
	for (std::size_t i = 0; i < indexTree.size(); i++ ) {
		std::cerr << "  ---->  + : " << indexTree[i] << std::endl;
	}
	
	// cocoa + coconut behaviors
	
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
		auto array = indexTree.valueForKeyPath(Number(i).stringValue() + u8".child");
		std::cerr << "    +-+ : " << i << std::endl;
		for (std::size_t j = 0; j < 3; j++ ) {
			std::cerr << "      + : [" << j <<  "] " << ref_cast<Array>(*array)[j] << std::endl;
		}
	}
	
	Array list = {
		String::with(u8"apple"),
		String::with(u8"Banana"),
		String::with(u8"Apple"),
		String::with(u8"baNana"),
		String::with(u8"bånAna"),
		String::with(u8"étourdie"),
		String::with(u8"éa"),
		String::with(u8"Cherry"),
		String::with(u8"åpple"),
		String::with(u8"Pear"),
		String::with(u8"epic"),
		String::with(u"\ub098\ub294\ud0dc\uc624")
	};
	
	auto sort = list.sortedArrayUsingSelectorKey(u8"@localizedCaseInsensitiveCompare:");
	for (const auto & str : Thus<Array>(sort)) {
		std::cerr << "    + : " << str << std::endl;
	}
	
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
	
	std::cerr << ages[{2,1}] << std::endl;
	
	Array keys = {
		String::with(u8"firstName"),
		String::with(u8"lastName"),
		String::with(u8"age")
	};
	
	MutableArray people;
	
	firstNames.enumerateObjectsUsingFunction(
		[&lastNames, &ages, &keys, &people] (const Owning<Any> & obj, std::size_t index, bool & stop)
	{
		people.addObject(
			Dictionary::with({
				{ keys[0], obj },
				{ keys[1], lastNames[index] },
				{ keys[2], ages[index] }
			})
		);
	}, EnumerationConcurrent);
	/*
	for (std::size_t i = 0 ; i < 4 ; i++) {
		people.addObject(
			Dictionary::with({
				{ keys[0], firstNames[i] },
				{ keys[1], lastNames[i] },
				{ keys[2], ages[i] }
			})
		);
	}
	*/
	/*
	Array people = {
		Dictionary::with({
			{ String::with(u8"firstName"), firstNames[0] },
			{ String::with(u8"lastName"), lastNames[0] },
			{ String::with(u8"age"), ages[0] }
		}),
		Dictionary::with({
			{ String::with(u8"firstName"), firstNames[1] },
			{ String::with(u8"lastName"), lastNames[1] },
			{ String::with(u8"age"), ages[1] }
		}),
		Dictionary::with({
			{ String::with(u8"firstName"), firstNames[2] },
			{ String::with(u8"lastName"), lastNames[2] },
			{ String::with(u8"age"), ages[2] }
		}),
		Dictionary::with({
			{ String::with(u8"firstName"), firstNames[3] },
			{ String::with(u8"lastName"), lastNames[3] },
			{ String::with(u8"age"), ages[3] }
		})
	};
	*/
	SortDescriptor s0(u8"firstName", false);
	SortDescriptor s1(u8"lastName", false);
	SortDescriptor s2(u8"age");
	
	Array people_sort = people.sortedArrayUsingDescriptors({ &s1, &s0 });
	
	for (Array::const_iterator it = people_sort.cbegin(); it != people_sort.cend(); ++it)
	{
		std::cerr << " + people_sort: " << ptr_cast<Dictionary>(*it)->objectForKey(u8"firstName") << std::endl;
		std::cerr << " + people_sort: " << ptr_cast<Dictionary>(*it)->objectForKey(u8"lastName") << std::endl;
	}
	
	MutableDictionary d;
	d[u8"héllo2"] = lastNames[1];
	d[u8"héllo1"] = lastNames[0];
	d[u8"héllo3"] = lastNames[2];
	d[u8"héllo4"] = String::with(u8"étourdie");
	
	
	for (Dictionary::const_iterator it = d.begin(); it != d.end(); ++it)
	{
		std::cerr << " + d: " << (*it).first << " = " <<  (*it).second << std::endl;
	}
#if 0
	
	std::string in = u8"+45666.123";
	
	String s(in);
	print_ref(s);
	
	
	std::cerr << "to_numeric: " << to_numeric<float>(in)  << std::endl;
	std::cerr << "stof: " << std::stof(in) << std::endl;

	std::cerr << "past: " << Date::distantPast()  << std::endl;
	std::cerr << "future: " << Date::distantFuture()  << std::endl;
	
	Owning<Any> now = Date::with();
	
	std::cerr << "now: " << now << std::endl;
	
	Data dt1("toto", 4);
	
	print_ref(dt1);
	
	encoding_option encoding;
	float confidence;
	//const char * bom = u8"\xEF\xBB\xBF";
	std::string hello = u8"hello & wérld!";
	ustring::guess_encoding(hello, encoding, confidence);
	
	std::cerr << "guess_encoding->codepage: " << ustring::get_codepage(encoding) << " " <<  to_string<std::string>(confidence, 1) << std::endl;
	
	std::string ret = ustring::make_utf8(hello, confidence, encoding_utf16);
	// expecting 0
	std::cerr << "guess_encoding: " << ret << " " << to_string<std::string>(confidence, 1) << std::endl;
	
	ret = ustring::make_utf8(hello, confidence, encoding_utf8);
	// expecting 0.8 -> return hello
	std::cerr << "guess_encoding: " << ret << " " << to_string<std::string>(confidence, 1) << std::endl;
	
	ret = ustring::make_utf8(hello, confidence, encoding_auto);
	// expecting 0.8 -> return new thru encoding detection
	std::cerr << "guess_encoding: " << ret << " " << to_string<std::string>(confidence, 1) << std::endl;
	
	std::cerr << "dt1: " <<  dt1.stringValue() << " " << &dt1 << std::endl;
	std::cerr << "dt1: " << dt1.hash() << std::endl;
	
	Data dt2(std::move(dt1));
	
	std::cerr << "dt1: " << dt1.stringValue() << " " << &dt1 << std::endl;
	std::cerr << "dt1: " << dt1.hash() << std::endl;
	
	std::cerr << "dt2: " << dt2.stringValue() << " " << &dt2 << std::endl;
	std::cerr << "dt2: " << dt2.hash() << std::endl;
	
	//Range rg1(0, 8);
	//Range rg2(8, 7);
	//Range rg3 = rg1.intersectionRange(rg2);
	
	//std::cerr << rg1 << std::endl;
	//std::cerr << rg2 << std::endl;
	//std::cerr << rg3 << std::endl;
	
	Array keys =
	{
		String::with(u8"key0"),
		String::with(u8"key0"),
		String::with(u8"key1"),
		String::with(u8"key2")
	};
	
	Array vals =
	{
		Number::with(0UL),
		Number::with(0UL),
		Number::with(1UL),
		Number::with(2UL)
	};
	
	Set keys_set(keys.cbegin(), keys.cend());
	for (Set::const_iterator it = keys_set.cbegin(); it != keys_set.cend(); ++it)
	{
		std::cerr << " keys_set: " << (*it) << std::endl;
		std::cerr << (*it).use_count() << std::endl;
	}
	
	for (Array::const_iterator it = keys.cbegin(); it != keys.cend(); ++it)
	{
		std::cerr << " keys: " << (*it) << std::endl;
		std::cerr << (*it).use_count() << std::endl;
	}
	
	Dictionary dict(keys.cbegin(), keys.cend(), vals.cbegin(), vals.cend());
	
	vals = {}; // reset count of val e.g -1
	
	for (Dictionary::const_iterator it = dict.cbegin(); it != dict.cend(); ++it)
	{
		std::cerr << "dict: '" << (*it).first << "' : '" << (*it).second << "'" << std::endl;
		std::cerr << (*it).first.use_count() << " : " << (*it).second.use_count() << std::endl;
	}
	
	Dictionary dict2(dict.cbegin(), dict.cend());
	
	for (Dictionary::const_iterator it = dict2.cbegin(); it != dict2.cend(); ++it)
	{
		std::cerr << "'" << (*it).first << "' : '" << (*it).second << "'" << std::endl;
		std::cerr << (*it).first.use_count() << " : " << (*it).second.use_count() << std::endl;
	}
	
	std::size_t idx = 0;
	std::vector<std::string> arr { "0s", "1s", "2s", "3s", "4s", "5s" };
	
	typedef std::vector<std::string>::const_iterator const_iterator;
	typedef std::vector<std::string>::const_reverse_iterator const_reverse_iterator;
	
	for (const_iterator it0 = arr.cbegin(); it0 != arr.cend(); ++it0) {
		idx = static_cast<std::size_t>(std::distance<const_iterator>(arr.cbegin(), it0));
		std::cerr << idx << " : '" << *it0 << "'" << std::endl;
	}
	
	std::cerr << "" << std::endl;
	
	for (const_reverse_iterator it1 = arr.crbegin(); it1 != arr.crend(); ++it1) {
		idx = static_cast<std::size_t>(std::distance<const_reverse_iterator>(it1, arr.crend() -1));
		std::cerr << idx << " : '" << *it1 << "'" << std::endl;
	}
	
#endif
	
	std::string u = u8"\u2215/\u2215";
	
	/*
	for (auto & c : u) {
		std::cerr << c << std::endl;
	}
	*/
	
	std::ios ios_fmt(nullptr);
	ios_fmt.copyfmt(std::cerr);
	
	std::string key = String(u).stringValue(); // UTF-8
	
	std::cerr << key << std::endl;
	
	for (char32_t c : key) { // 1 to 4 then max 4
		std::cerr << std::hex << std::showbase << c << std::endl;
	}
	
	//std::ios::fmtflags ios_fmtflags(std::cerr.flags());
	
	std::u16string key16 = String(u).string16Value();
	/*
	for (auto & c : key16) {
		std::cerr << std::hex << std::showbase << c << std::endl;
	}
	*/
	
	key16 = unicode::utf8_to_utf16(u);
	for (auto & c : key16) {
		std::wcerr << std::hex << std::showbase << c << std::endl;
	}
	
	std::cerr.copyfmt(ios_fmt);
	
	//std::cerr.flags(ios_fmtflags);

#if 0
	
	{
		std::set<std::string> codepages;
		if(ustring::get_codepages(codepages)) {
			for (auto & codepage : codepages) {
				std::cerr << "+ get_codepages : " << codepage << std::endl;
			}
		}
	}
	std::cerr << "+-+"  << std::endl;
	{
		std::vector<std::string> codepages;
		if(ustring::get_sys_codepages(codepages)) {
			for (auto & codepage : codepages) {
				std::cerr << "+ get_sys_codepages : " << codepage << std::endl;
			}
		}
	}
#endif
}

int main(int argc, const char * argv[])
{
	std::int32_t in_0 = -18;
	std::uint8_t out_0[4];
	runtime::byteorder::w32be(in_0, out_0);
	
	std::cerr << "+ out_0 " << out_0 << std::endl;
	
	std::uint8_t in_1[4] = { out_0[0], out_0[1], out_0[2], out_0[3] };
	std::int32_t out_1;
	runtime::byteorder::r32be_v2(in_1, out_1);
	
	std::cerr << "+ out_1 " << out_1 << std::endl;
	
	Range rg = { 0, 10 };
	
	std::cerr << "+ rg " << rg << std::endl;
	
	OptionalReturn<Owning<Data>, Owning<Error>> ret;
	
	ret.valid = true;
	ret.success = Data::with();
	
	if (ret) {
		std::cerr << "+ true " << ret() << std::endl;
	}
	
	ret.valid = false;
	ret.error = Error::with();
	
	if (!ret) {
		std::cerr << "+ false " << ~ret << std::endl;
	}
	
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
	
	using namespace std;
	
	String str_16 = u"étourdissement 나는태오";

	String str_fmt = String::format
	(
		u"%S %llu %g %s %S %d %g %s %S \ub098\ub294\ud0dc\uc624 %llu %g",
		str_16.string16Value().c_str(),
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

	String oUmlaut = u"\u00f6"; // o-umlaut
	String oPlusUmlaut = u"o\u0308";

	cout << "[ oUmlaut " << (oUmlaut.compare(oPlusUmlaut) == OrderedSame) << "] " << endl;
	cout << "[ oUmlaut " << oUmlaut.localizedCompare(oPlusUmlaut) << "] " << endl;

	cout << "[ oUmlaut == oPlusUmlaut " << (oUmlaut == oPlusUmlaut) << "] " << endl;

	cout << "[ oUmlaut == oPlusUmlaut " << (oUmlaut == u"o\u0308") << "] " << endl;

	String str_fmt2;

	String str_other2 = str_fmt2.stringByAppendingFormat
	(
		 u"%S %llu %g %s %S %d %g %s %S \ub098\ub294\ud0dc\uc624 %llu %g",
		 str_16.string16Value().c_str(),
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

	cout << "[" << str_16 << "] " << endl;

	Owning<String> str_other = String::with(str_fmt);

	cout << "[" << str_fmt << "] " << endl;
	cout << "[" << str_other << "] " << endl;
	cout << "[" << str_other2 << "] " << endl;
	
	wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t> convert;
		
	//u16string utf16 = u"\ub098\ub294\ud0dc\uc624";
	
	u16string utf16 = u"나는태오";
	
	cout << hex << "UTF-16\n\n";
	for (char16_t c : utf16)
		cout << "[" << c << "] ";
		
	string utf8 = convert.to_bytes(utf16);
		
	cout << "\n\nUTF-16 to UTF-8\n\n";
	for (unsigned char c : utf8)
		cout << "[" << int(c) << "] ";
	
	cout << "[" << utf8 << "] ";
	
	cout << "\n\nConverting back to UTF-16\n\n";
		
	utf16 = convert.from_bytes(utf8);
		
	for (char16_t c : utf16)
		cout << "[" << c << "] ";
	cout << endl;
	
	auto job0 = JobExec([]() -> bool
	{
		auto job1 = JobExec([]() -> bool
		{
			/* do job */
			test_stuff();
			test_attr_and_custom();
			//test_date();
			//test_number();
			//test_array();
			return true;
		});
		bool result = job1.get();
		std::cerr << "+ result : " << result << std::endl;
		return result;
	});
	bool result = job0.get();
	std::cerr << "+ result : " << result << std::endl;
	
	return 0;
}

/* EOF */