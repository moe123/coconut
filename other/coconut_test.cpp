//
// coconut_test.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <other/coconut_test_attrs.hpp>

using namespace coconut;

/*
COCONUT_SECTION_INI
{
	std::cerr << " _init " << std::endl;
}

COCONUT_SECTION_FINI
{
	std::cerr << " _fini " << std::endl;
}
*/
const Owning<Any> operator "" _U(const char * in, std::size_t sz)
{ return With<String>(in); }
	
const Owning<Any> operator "" _U(const char16_t * in, std::size_t sz)
{ return With<String>(in); }
	
const Owning<Any> operator "" _U(long double in)
{ return With<Number>(in); }
	
const Owning<Any> operator "" _U(unsigned long long in)
{ return With<Number>(in); }
	
static void print_ref(const Any & ref)
{
	auto array = With<Array>
	({
		With<String>(u8"hello"),
		With<Number>(10),
		With<Number>(10.8),
		With<Date>()
	});
	
	auto array1 = With<Array>(Thus<Array>(array));
	
	std::cerr.setf(std::ios::fixed, std::ios::floatfield);
	std::cerr.precision(10);
	
	std::cerr << "+ description() : " << ref.description() << std::endl;
	std::cerr << "+ className() : " << ref.className() << std::endl;
	std::cerr << "+ classTree() : " << ref.classTree() << std::endl;
	
	//std::cerr << ref << std::endl;
	std::cerr << "+ stringValue() : " << ref.stringValue() << std::endl;
	
	std::cerr << "+ floatValue() : " << ref.floatValue() << std::endl;
	std::cerr << "+ doubleValue() : " << ref.doubleValue() << std::endl;
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
	if (sz && sz->unsignedLongValue() > 5UL) {
		d.setValueForKeyPath(u8"unicøde.3.ßtring.5", ...);
	}
	
	// or
	auto arr = d.valueForKeyPath(u8"unicøde.3.ßtring");
	if (arr && arr->isKindOf(MutableArrayClass)) {
		if (ref_cast<MutableArray>(*arr).size() > 5) {
			d.setValueForKeyPath(u8"unicøde.3.ßtring.5", ...);
		}
	}
	
	// or
	auto arr = d.valueForKeyPath(u8"unicøde.3.ßtring");
	if (arr && arr->isKindOf(MutableArrayClass)) {
		if (ref_cast<MutableArray>(*arr).size() > 5UL) {
			ref_cast<MutableArray>(*arr).replaceObjectAtIndex(
				5,
				With<String>(u8"an unicøde ßtring")
			);
		}
	}
	
	// or
	Owning<MutableArray> arr = ptr_cast<MutableArray>(
		d.valueForKeyPath(u8"unicøde.3.ßtring")
	);
	if(arr && arr->size() > 5) {
		arr->replaceObjectAtIndex(5, With<String>(u8"an unicøde ßtring"));
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
		Copy<Number>(n0),
		Copy<Number>(n1),
		Copy<Number>(n2),
		Copy<Number>(n3),
		Copy<Number>(n4),
		Copy<Number>(n5),
		Copy<Number>(n6),
		Copy<Number>(n7),
		Copy<Number>(n8),
		Copy<Number>(n3),
		Copy<Number>(n4),
		Copy<Number>(n5),
		Copy<Number>(n6),
		Copy<Number>(n7),
		Copy<Number>(n8)
	};
	
	if (ConformsTo<Array>(a)) {
		std::cerr << " + ConformsTo<Array>(a) " << std::endl;
	}
	
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
	
	a.performSelectorKeyAfterDelay(10000, false, u8"@isEqual:", With<None>());
	
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
			std::cerr << "indexOfObjectPassingTest idx : " << index << " obj: " <<  obj << " this_thread  : " << std::this_thread::get_id() << std::endl;
			return true;
		}
		return false;
	}, EnumerationConcurrent);
	
	//std::this_thread::sleep_for(std::chrono::microseconds(500));
	
	std::cerr << "indexOfObjectPassingTest idx : " << idx << std::endl;

	
	Owning<Array> aa = With<Array>
	({
		a[0], // increasing ref count &n0 [a copied]
		a[1], // increasing ref count  &n1 [a copied]
		a[2] // increasing ref count &n2 [a copied]
	});
	
	print_array(a);
	
	Owning<Array> b = With<Array>(a, CopyKind);
	
	Owning<Array> bb = With<Array>
	(
		b->begin(),
		b->end(),
		CopyMutable
	);
	
	print_array(*b);
	
	Owning<Number> n00 = With<Number>(1L);
	Owning<Any> n11 = With<Number>(4U);
	Owning<Number> n22 = With<Number>(-3L);
	auto n33 = With<Number>(n2);
	
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
	
	Path path = { u8"/usr/bin" };
	
	std::cerr << " path = " << path << std::endl;
	
	URL url = u8"/usr/bin";
	
	std::cerr << " url = " << url << std::endl;
	
	MutableArray tree;
	for (std::size_t i = 0; i < 10; i++ ) {
		auto child = With<Dictionary>({
			{ With<String>(u8"child"), With<Number>(i + 1) }
		});
		auto parent = With<Dictionary>({
			{ With<String>(u8"parent"), child }

		});
		tree += parent;
	}
	
	auto values = tree.valueForKeyPath(u8"parent.child");
	
	Then<Array>(*values);
	Thus<Array>(tree);
	
	if (KindOf<Array>(values)) {
		for (const auto & number : Thus<Array>(values)) {
			std::cerr << " number  + : " << number << std::endl;
		}
	}
	
	MutableArray indexTree;
	
	for (std::size_t i = 0; i < 10; i++ ) {
		auto child = With<Dictionary>({
			{ With<String>(u8"child"), With<Number>(i + 1) }
		});
		auto parent = With<Array>({
			child
		});
		indexTree += parent;
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
	
	indexTree.enumerateObjectsUsingFunction(
		[&indexTree] (const Owning<Any> & obj, std::size_t index, bool & stop)
	{
		auto num = indexTree.valueForKeyPath(Number(index).stringValue() + u8".0.child");
		std::cerr << "+ index : " << index << "], valueForKeyPath : " << num << std::endl;
	}, EnumerationConcurrent|EnumerationReverse);
	
	for (std::size_t i = 0; i < 10; i++ ) {
		auto num = indexTree.valueForKeyPath(Number(i).stringValue() + u8".0.child");
		std::cerr << "indexTree    + : " << num << std::endl;
	}
	
	// out of bounds capacity, seeing index as key-like,
	// subscripting, script language
	// to use with moderation
	
	indexTree[MaxFound] = With<String>(u8"étourdie"); // push_back
	indexTree[MaxFound] = With<Date>(); // push_back
	
	for (std::size_t i = 0; i < indexTree.size(); i++ ) {
		std::cerr << "  ---->  + : " << indexTree[i] << std::endl;
	}
	
	// cocoa + coconut behaviors
	
	// indexTree = {};
	indexTree.removeAllObjects();
	for (std::size_t i = 0; i < 10; i++ ) {
		auto child = With<Dictionary>({
			{ With<String>(u8"child"), With<Number>(i + 1) }
		});
		auto parent = With<Array>({
			child,
			child,
			child
		});
		indexTree += parent;
	}
	
	for (std::size_t i = 0; i < 10; i++ ) {
		auto array = indexTree.valueForKeyPath(Number(i).stringValue() + u8".child");
		std::cerr << "indexTree2 +-+ : " << i << std::endl;
		for (std::size_t j = 0; j < 3; j++ ) {
			std::cerr << "      + : [" << j <<  "] " << ref_cast<Array>(*array)[j] << std::endl;
		}
	}
	
	Array list = {
		With<String>(u8"apple"),
		With<String>(u8"Banana"),
		With<String>(u8"Apple"),
		With<String>(u8"baNana"),
		With<String>(u8"bånAna"),
		With<String>(u8"étourdie"),
		With<String>(u8"éa"),
		With<String>(u8"Cherry"),
		With<String>(u8"åpple"),
		With<String>(u8"Pear"),
		With<String>(u8"epic"),
		With<String>(u"\ub098\ub294\ud0dc\uc624")
	};
	
	auto sort = list.sortedArrayUsingSelectorKey(u8"@localizedCaseInsensitiveCompare:");
	for (const auto & str : Thus<Array>(sort)) {
		std::cerr << "    + : " << str << std::endl;
	}
	
	Array firstNames = {
		With<String>(u8"Alice"),
		With<String>(u8"Bob"),
		With<String>(u8"Charlie"),
		With<String>(u8"Quentin")
	};
	
	Array lastNames = {
		With<String>(u8"Smith"),
		With<String>(u8"Jones"),
		With<String>(u8"Smith"),
		With<String>(u8"Alberts")
	};
	
	Array ages = {
		With<Number>(24),
		With<Number>(27),
		With<Number>(33),
		With<Number>(31)
	};
	
	auto names = firstNames + With<String>(u8"Alberts") + Number(44) + Date();
	for (const auto & name : Thus<Array>(names)) {
		std::cerr << " + name + : " << name << std::endl;
	}
	
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
	
	struct hello
	{
		virtual ~hello() {}
	};
	
	hello world;
	
	std::cerr << " + ConformsTo<Dictionary> names  + : " << ConformsTo<Dictionary>(names) << std::endl;
	std::cerr << " + ConformsTo<Array> names  + : " << ConformsTo<Array>(names) << std::endl;
	std::cerr << " + ConformsTo<Any> world  + : " << ConformsTo<Any>(world) << std::endl;
	
	for (const auto & age : ages[{-2,1}]) {
		std::cerr << " + age  + : " << age << std::endl;
	}
	
	Array keys = {
		With<String>(u8"firstName"),
		With<String>(u8"lastName"),
		With<String>(u8"age")
	};
	
	MutableArray people;
	
	Enumerate<Array>(firstNames,
		[&lastNames, &ages, &keys, &people] (const Owning<Any> & obj, std::size_t index, bool & stop)
	{
		people.addObject(
			With<Dictionary>({
				{ keys[0], obj },
				{ keys[1], lastNames[index] },
				{ keys[2], ages[index] }
			})
		);
	}, EnumerationConcurrent);

	Enumerate<Array>(firstNames,
		[] (const Owning<Any> & obj)
	{

	}, EnumerationConcurrent);
	
	/*
	for (std::size_t i = 0 ; i < 4 ; i++) {
		people.addObject(
			With<Dictionary>({
				{ keys[0], firstNames[i] },
				{ keys[1], lastNames[i] },
				{ keys[2], ages[i] }
			})
		);
	}
	*/
	/*
	Array people = {
		With<Dictionary>({
			{ With<String>(u8"firstName"), firstNames[0] },
			{ With<String>(u8"lastName"), lastNames[0] },
			{ With<String>(u8"age"), ages[0] }
		}),
		With<Dictionary>({
			{ With<String>(u8"firstName"), firstNames[1] },
			{ With<String>(u8"lastName"), lastNames[1] },
			{ With<String>(u8"age"), ages[1] }
		}),
		With<Dictionary>({
			{ With<String>(u8"firstName"), firstNames[2] },
			{ With<String>(u8"lastName"), lastNames[2] },
			{ With<String>(u8"age"), ages[2] }
		}),
		With<Dictionary>({
			{ With<String>(u8"firstName"), firstNames[3] },
			{ With<String>(u8"lastName"), lastNames[3] },
			{ With<String>(u8"age"), ages[3] }
		})
	};
	*/
	SortDescriptor s0(u8"firstName", true);
	SortDescriptor s1(u8"lastName", false);
	SortDescriptor s2(u8"age");
	
	auto people_sort = people.sortedArrayUsingDescriptors({ &s1, &s0 });
	
	for (Array::const_iterator it = people_sort.cbegin(); it != people_sort.cend(); ++it)
	{
		std::cerr << " + people_sort: " << Thus<Dictionary>(*it)[u8"firstName"] << std::endl;
		std::cerr << " + people_sort: " << Then<Dictionary>(*it)->objectForKey(u8"lastName") << std::endl;
	}
	
	MutableDictionary hellos;
	hellos[u8"héllo 2"] = lastNames[1];
	hellos[u8"héllo 1"] = lastNames[0];
	hellos[u8"héllo 3"] = lastNames[2];
	hellos[u8"héllo 4"] = With<String>(u8"étourdie");
	
	std::cerr << " + d[héllo 4]: " << Then<Dictionary>(hellos)->objectForKey(u8"héllo4") << std::endl;
	
	for (Dictionary::const_iterator it = hellos.cbegin(); it != hellos.cend(); ++it)
	{
		std::cerr << " + hellos: " << (*it).first << " = " <<  (*it).second << std::endl;
	}
	
	Enumerate<Dictionary>(hellos,
		[] (const Owning<Any> & key, const Owning<Any> & obj, bool & stop)
	{
		std::cerr << " + key: " << key << " = " <<  obj << std::endl;
	}, EnumerationConcurrent|EnumerationReverse);
	
#if 0
	
	std::string in = u8"+45666.123";
	
	String s(in);
	print_ref(s);
	
	
	std::cerr << "to_numeric: " << to_numeric<float>(in)  << std::endl;
	std::cerr << "stof: " << std::stof(in) << std::endl;

	std::cerr << "past: " << Date::distantPast()  << std::endl;
	std::cerr << "future: " << Date::distantFuture()  << std::endl;
	
	Owning<Any> now = With<Date>();
	
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
		With<String>(u8"key0"),
		With<String>(u8"key0"),
		With<String>(u8"key1"),
		With<String>(u8"key2")
	};
	
	Array vals =
	{
		With<Number>(0UL),
		With<Number>(0UL),
		With<Number>(1UL),
		With<Number>(2UL)
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
		ustring::get_codepages(codepages);
		{
			for (auto & codepage : codepages) {
				std::cerr << "+ get_codepages : " << codepage << std::endl;
			}
		}
	}
	std::cerr << "+-+"  << std::endl;
	{
		std::vector<std::string> codepages;
		if (ustring::get_sys_codepages(codepages)) {
			for (auto & codepage : codepages) {
				std::cerr << "+ get_sys_codepages : " << codepage << std::endl;
			}
		}
	}
#endif
}
	
static void test_getlocale()
{
	std::string id;
	char * q;
	std::vector<std::string> lc;
	
	setlocale(LC_ALL, "");
	
	q = std::getenv("LANG");
	lc.push_back((q != NULL ? q : ""));
	
	q = setlocale(LC_ALL, NULL);
	lc.push_back((q != NULL ? q : ""));
	
	q = setlocale(LC_CTYPE, NULL);
	lc.push_back((q != NULL ? q : ""));
	
	q = setlocale(LC_COLLATE, NULL);
	lc.push_back((q != NULL ? q : ""));
	
	q = setlocale(LC_MESSAGES, NULL);
	lc.push_back((q != NULL ? q : ""));
	
	q = setlocale(LC_MONETARY, NULL);
	lc.push_back((q != NULL ? q : ""));
	
	q = setlocale(LC_NUMERIC, NULL);
	lc.push_back((q != NULL ? q : ""));
	
	q = setlocale(LC_TIME, NULL);
	lc.push_back((q != NULL ? q : ""));
	
	for (std::vector<std::string>::const_iterator it = lc.begin(); it != lc.end(); ++it) {
		if ((*it).size() >= 5) {
			std::size_t found = (*it).find_first_of(".");
			if (found != std::string::npos) {
				id = (*it).substr (0, found);
			} else {
				id = (*it);
			}
			id = (*it);
			break;
		}
	}
	if (!id.size()) {
		id = uloc_getDefault();
	}
	if (id.size() < 5) {
		id = u8"en_US_POSIX";
	}
	
	std::cerr << "+ id " << id << std::endl;
}

static void parse_path(void)
{
	runtime::traits::irange rg(u8"{\"location\" : 45, \"length\" : 78}");
	
	std::cerr << "+ rg " << rg.to_string() << std::endl;
	
	std::string in = u8"C:\\a/toto";
	
	std::smatch iswin_match;
	std::ssub_match sub_match;
	std::regex iswin_regex{R"(^(\\|/|)([a-zA-z]:)(\\|/)(.*)$)"};
	
	if (std::regex_match(in, iswin_match, iswin_regex)) {
		if (iswin_match.size() == 5) {
			std::smatch iswin_ntfs_match;
			
			sub_match = iswin_match[1];
			
			std::cerr << "+ sub_match first separator " << sub_match.str() << std::endl;
			
			sub_match = iswin_match[2];
			
			std::cerr << "+ sub_match drive " << sub_match.str() << std::endl;
			
			sub_match = iswin_match[3];
			
			std::cerr << "+ sub_match separator " << sub_match.str() << std::endl;
			
			try
			{
				std::regex iswin_ntfs_regex{R"(^[a-zA-Z]:\\(((?![<>:\"/\\|?*]).)*[^ ](\\|/))*((?![<>:\"/\\|?*]).)*[^ ](\\|/)?$)"};
				if (std::regex_match(in, iswin_ntfs_match, iswin_ntfs_regex)) {
					std::cerr << "+ parse_path " << std::endl;
				}
			}
			catch(const std::regex_error & e)
			{
				std::cerr << e.what() << ". Code: " << e.code() << std::endl;
				
				switch (e.code())
				{
					case std::regex_constants::error_collate:
						std::cerr << "The expression contained an invalid collating element name.";
						break;
					case std::regex_constants::error_ctype:
						std::cerr << "The expression contained an invalid character class name.";
						break;
					case std::regex_constants::error_escape:
						std::cerr << "The expression contained an invalid escaped character, or a trailing escape.";
						break;
					case std::regex_constants::error_backref:
						std::cerr << "The expression contained an invalid back reference.";
						break;
					case std::regex_constants::error_brack:
						std::cerr << "The expression contained mismatched brackets ([ and ]).";
						break;
					case std::regex_constants::error_paren:
						std::cerr << "The expression contained mismatched parentheses (( and )).";
						break;
					case std::regex_constants::error_brace:
						std::cerr << "The expression contained mismatched braces ({ and }).";
						break;
					case std::regex_constants::error_badbrace:
						std::cerr << "The expression contained an invalid range between braces ({ and }).";
						break;
					case std::regex_constants::error_range:
						std::cerr << "The expression contained an invalid character range.";
						break;
					case std::regex_constants::error_space:
						std::cerr << "There was insufficient memory to convert the expression into a finite state machine.";
						break;
					case std::regex_constants::error_badrepeat:
						std::cerr << "The expression contained a repeat specifier (one of *?+{) that was not preceded by a valid regular expression.";
						break;
					case std::regex_constants::error_complexity:
						std::cerr << "The complexity of an attempted match against a regular expression exceeded a pre-set level.";
						break;
					case std::regex_constants::error_stack:
						std::cerr << "There was insufficient memory to determine whether the regular expression could match the specified character sequence.";
						break;
					default:
						std::cerr << "Undefined.";
						break;
						
				}
				std::cerr << std::endl;
			}
			
			
		}
		/*
		std::cerr << "+ parse_path " << std::endl;
		sub_match = match[1];
		std::cerr << "+ match.size() " << match.size() << std::endl;
		std::cerr << "+ match[1] " << sub_match.str() << std::endl;
		
		if (match.size() == 3) {
			sub_match = match[1];
		}
		*/
	}
}

static std::pair<int, bool> is_prime(int n)
{
	std::cout << "is_prime " << n << std::endl;
	for (int i = 2; i < n; i++) {
		if (n % i == 0) { return std::make_pair(i, false); }
	}
	return std::make_pair(n, true);
}

static void run_queue(void)
{
	//std::cout << "sizeof(class std::string) : " << sizeof(std::string) << std::endl;
	//std::cout << "sizeof(class Owning<Any>) : " << sizeof(Owning<Any>) << std::endl;
	//std::cout << "sizeof(std::map<Owning<Any>, Owning<Any>, std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> >) : " << sizeof(std::map<Owning<Any>, Owning<Any>, std::function<bool(const Owning<Any> & a, const Owning<Any> & b)> >) << std::endl;
	//std::cout << "sizeof(std::map<Owning<Any>, Owning<Any>, bool (*) (const Owning<Any> & a, const Owning<Any> & b) >) : " << sizeof(std::map<Owning<Any>, Owning<Any>, bool (*) (const Owning<Any> & a, const Owning<Any> & b) >) << std::endl;
	
	std::cout << "sizeof(class runtime::traits::bytebuf) : " << sizeof(runtime::traits::bytebuf) << std::endl;
	std::cout << "sizeof(class runtime::traits::uri) : " << sizeof(runtime::traits::uri) << std::endl;
	std::cout << "sizeof(class runtime::traits::ustring) : " << sizeof(runtime::traits::ustring) << std::endl;
	std::cout << "sizeof(class runtime::traits::upath) : " << sizeof(runtime::traits::upath) << std::endl;
	std::cout << "sizeof(class runtime::traits::numeric) : " << sizeof(runtime::traits::numeric) << std::endl;
	std::cout << "sizeof(class runtime::traits::datetime) : " << sizeof(runtime::traits::datetime) << std::endl;
	
	//std::cout << "sizeof(class icu::UnicodeString) : " << sizeof(icu::UnicodeString) << std::endl;
	
	std::cout << "sizeof(class runtime::nucleus) : " << sizeof(runtime::nucleus) << std::endl;
	std::cout << "sizeof(class Object) : " << sizeof(Object) << std::endl;
	std::cout << "sizeof(class Array) : " << sizeof(Array) << std::endl;
	std::cout << "sizeof(class MutableArray) : " << sizeof(MutableArray) << std::endl;
	std::cout << "sizeof(class Dictionary) : " << sizeof(Dictionary) << std::endl;
	std::cout << "sizeof(class MutableDictionary) : " << sizeof(MutableDictionary) << std::endl;
	std::cout << "sizeof(class String) : " << sizeof(String) << std::endl;
	std::cout << "sizeof(class Number) : " << sizeof(Number) << std::endl;
	std::cout << "sizeof(class Date) : " << sizeof(Date) << std::endl;
	std::cout << "sizeof(class Data) : " << sizeof(Data) << std::endl;
	std::cout << "sizeof(class URL) : " << sizeof(URL) << std::endl;
	
	// testing any return types even if only void makes sense.
	
	COCONUT_DEFER ([]() -> int { std::cout << "lambda" << std::endl; return 1; });
	COCONUT_DEFER (is_prime, 300);
	
	for (std::size_t i = 0 ; i < 10 ; i++) {
		// not working in loop scope, same effect than calling the function
		// directly without the functor (BTW, real functor decorator) wrapper overheads.
		COCONUT_DEFER (is_prime, i);
	}
	
	JobPool pool {4};
	std::vector< JobReturn< std::pair<int, bool> > > tasks;
	for (int i = 0; i < 10; i++) {
		tasks.push_back(pool(
			[i] (int ii) -> std::pair<int, bool> {
				return std::make_pair(i * ii, (i * ii) % 2);
			}, i));
	}
	for (auto i = tasks.begin(); i != tasks.end(); i++) {
		auto n = (*i)();
		std::cout << "+ is_odd : " <<  n.first << " -> " << std::boolalpha << n.second << std::endl;
	}
	
	return;
}

int Σ0() {
	return 0;
}

// ȡ

int main(int argc, const char * argv[])
{
	{
		runtime::traits::irange rg0{3, 15};
		std::cerr << "+ to_string " << rg0.to_string() << std::endl;
		
		runtime::traits::irange rg1{rg0.to_string()};
		
		std::cerr << "+ to_string " << rg1.to_string() << std::endl;
		
		runtime::traits::islice slc0{3, 15};
		std::cerr << "+ to_string " << slc0.to_string() << std::endl;
		
		runtime::traits::islice slc1{slc0.to_string()};
		
		std::cerr << "+ to_string " << slc1.to_string() << std::endl;
		
	}
	run_queue();
	{
		// testing if right shifting not screwing up signed e.g prefilling unsigned cast.
		std::int32_t in_0 = -888888888;
		std::uint8_t out_0[4];
		runtime::byteorder::w32le(in_0, out_0);
		
		std::cerr << "+ out_0 " << out_0 << std::endl;
		
		for (std::size_t i = 0 ; i < 4 ; i++) {
			std::cerr << "+ out_0[] " << unsafe_cast<std::uint32_t>(out_0[i]) << std::endl;
		}
		
		runtime::byteorder::w32be(in_0, out_0);
		
		for (std::size_t i = 0 ; i < 4 ; i++) {
			std::cerr << "+ out_0[] " << unsafe_cast<std::uint32_t>(out_0[i]) << std::endl;
		}
		
		std::uint8_t in_1[4] = { out_0[0], out_0[1], out_0[2], out_0[3] };
		std::int32_t out_1;
		runtime::byteorder::r32be(in_1, unsafe_cast<std::uint32_t &>(out_1));
		
		std::cerr << "+ out_1 " << out_1 << std::endl;
		
		runtime::byteorder::rs32be(in_1, out_1);
		
		std::cerr << "+ out_1 " << out_1 << std::endl;
	}
	
	{
		Array firstNames = {
			With<String>(u8"Alice"),
			With<String>(u8"Bob"),
			With<String>(u8"Charlie"),
			With<String>(u8"Quentin")
		};
		
		Array lastNames = {
			With<String>(u8"Smith"),
			With<String>(u8"Jones"),
			With<String>(u8"Smith"),
			With<String>(u8"Alberts")
		};
		
		Array ages = {
			With<Number>(24),
			With<Number>(27),
			With<Number>(33),
			With<Number>(31)
		};

		Array keys = {
			With<String>(u8"firstName"),
			With<String>(u8"lastName"),
			With<String>(u8"age")
		};
		
		MutableArray people;
		
		Enumerate<Array>(firstNames,
			[&] (const Owning<Any> & obj, std::size_t index, bool & stop)
		{
		 	people.addObject(
				With<Dictionary>({
					{ keys[0], obj },
					{ keys[1], lastNames[index] },
					{ keys[2], ages[index] }
				})
			);
		}, EnumerationConcurrent);
		
		SortDescriptor s0 {u8"firstName", false};
		SortDescriptor s1 {u8"lastName", false};
		SortDescriptor s2 {u8"age"};
		
		auto sorted = people.sortedArrayUsingDescriptors({ &s1, &s0 });
		
		std::cerr << "+ sorted : " << sorted << std::endl;
		
		Array people_ = Shift<Array>(sorted);
		
		std::cerr << "+ sorted : " << sorted << std::endl;
		
		std::cerr << "+ people_ : " << people_ << std::endl;
	}
	
	{
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
		std::cerr << "+ tree : " << tree << std::endl;
	}
	
	{
		MutableArray list = {
			With<String>(u8"apple"),
			With<String>(u8"Banana"),
			With<String>(u8"Apple"),
			With<String>(u8"baNana"),
			With<String>(u8"bånAna"),
			With<String>(u8"étourdie"),
			With<String>(u8"éa"),
			With<String>(u8"Cherry"),
			With<String>(u8"åpple"),
			With<String>(u8"Pear"),
			With<String>(u8"epic"),
			With<Date>(),
			With<Data>(reinterpret_cast<const std::uint16_t *>(u"\ub098\ub294\ud0dc\uc624"), 4, DataPackingLittleEndian),
			With<String>(u"\ub098\ub294\ud0dc\uc624")
		};
		list += list;
		std::cerr << "+ list : " << list << std::endl;
		
		auto sorted = list.sortedArrayUsingSelectorKey(u8"@localizedCaseInsensitiveCompare:");
		
		std::cerr << "+ sorted : " << sorted << std::endl;
	}
	
	{
		MutableArray indexTree;
		
		for (std::size_t i = 0; i < 10; i++ ) {
			auto child = With<Dictionary>({
				{ With<String>(u8"child"), With<Number>(i + 1) }
			});
			auto parent = With<Array>({
				child
			});
			indexTree += parent;
		}
		std::cerr << "+ indexTree : " << indexTree << std::endl;
	}
	
	String hello = u8"hello";
	{
		// public API to be considered off limit
		auto self = hello.valueForKey(u8"@self");
		
		std::cerr << "+ self : " << self << std::endl;
		
		// selector operator recursion-proof
		self = hello.valueForKey(u8"@self.@stringValue");
		
		std::cerr << "+ self : " << self << std::endl;
		std::cerr << "+ self unique ? : " << self.unique() << std::endl;
		// normal usage
		self = hello.valueForKeyPath(u8"@self.@stringValue");
		{
			auto self1 = self;
			std::cerr << "+ self count ? : " << self.use_count() << std::endl;
			std::cerr << "+ self unique ? : " << self.unique() << std::endl;
			std::cerr << "+ self1 : " << self1 << std::endl;
		}
		std::cerr << "+ self : " << self << std::endl;
		std::cerr << "+ self unique ? : " << self.unique() << std::endl;
		std::cerr << "+ self count ? : " << self.use_count() << std::endl;
	}
	
	std::cerr << "+ hello : " << hello << std::endl;
	
	//test_stuff();
	String s_0 = u"\u00f6";
	String s_1 = u"o\u0308";
	
	if (s_0 == s_1) {}
	
	StringSearchOptions opt_0 = StringSearchLiteral | StringSearchBackwards;
	StringSearchOptions opt_1 = StringSearchLiteral | StringSearchNumeric;
	
	std::cerr << runtime::algorithm::to_binary(opt_0) << std::endl;
	std::cerr << runtime::algorithm::to_binary(opt_1) << std::endl;
	
	Data dt_0 = { "some bytes", 10 };
	
	Path p_0 = u8"C:\\toto\\tata";
	
	std::cerr << "+ p_0 : " << p_0 << std::endl;
	
	for (const auto & byte : dt_0) {
		std::cerr << std::hex << std::showbase << int(byte) << std::endl;
	}
	
	auto job_0 = JobRun([]() -> bool
	{
		JobRun([]() -> void { });
		return true;
	});
	std::cerr << "+ job_0 : " << job_0 << std::endl;
	
	//run_queue();
	//parse_path();
	
	return 0;
	
	test_getlocale();
	test_getlocale();
	test_getlocale();
	
	Range rg0 = { 0, 10 };
	Range rg1 = { 3, 2 };
	
	Range rg2 = rg0.intersectionRange(rg1);
	
	for (auto i : rg2)
		std::cout << "[" << i << "] " << std::endl;
	
	std::cerr << "+ rg2 " << rg2 << std::endl;
	
	std::cerr << "+ sizeof(int) " << sizeof(int) << std::endl;
	
	Data dt = { "some bytes", 10 };
	
	for (auto byte : dt)
		std::cerr << std::hex << std::showbase << int(byte) << std::endl;
	
	std::int32_t in_0 = -18;
	std::uint8_t out_0[4];
	runtime::byteorder::w32be(in_0, out_0);
	
	std::cerr << "+ out_0 " << out_0 << std::endl;
	
	std::uint8_t in_1[4] = { out_0[0], out_0[1], out_0[2], out_0[3] };
	std::int32_t out_1;
	runtime::byteorder::rs32be(in_1, out_1);
	
	std::cerr << "+ out_1 " << out_1 << std::endl;
	
	Range rg = { 0, 10 };
	
	std::cerr << "+ rg " << rg << std::endl;
	
	OptionalReturn<bool, std::string> ret0;
	
	OptionalReturn< Owning<Data>, Owning<Error> > ret;
	
	ret.setSuccess(With<Data>());
	
	if (ret) {
		std::cerr << "+ true " << ret() << std::endl;
	}
	
	ret.setError(With<Error>());
	
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
		auto job_2 = JobExec(JobPolicyAsync, [&job_1, &res_1]() -> bool
		{
			std::cerr << "+ job_2 " << std::endl;
			res_1 = job_1();
			return true;
		});
		
		bool res_2 = job_2();
		
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

	Owning<String> str_other = With<String>(str_fmt);

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
		JobExec([]() -> void
		{
			/* do job */
			test_stuff();
			//test_attr_and_custom();
			//test_date();
			//test_number();
			//test_array();
			//return true;
		});
		//bool result = job1.get();
		//std::cerr << "+ result : " << job1 << std::endl;
		return true;
	});
	//bool result = job0.get();
	//std::cerr << "+ result : " << job0.get(); << std::endl;
	
	return 0;
}

/* EOF */