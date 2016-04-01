//
// Object.cpp
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>
#include <coconut/foundation/Array.hpp>
#include <coconut/foundation/Dictionary.hpp>
#include <coconut/foundation/None.hpp>
#include <coconut/foundation/Number.hpp>
#include <coconut/foundation/OrderedSet.hpp>
#include <coconut/foundation/Set.hpp>
#include <coconut/foundation/String.hpp>

using namespace coconut;

Object::Object() :
	Object(ObjectClass)
{ /* NOP */ }

Object::Object(const Object & obj) :
	Object(ObjectClass)
{ COCONUT_UNUSED(obj); }

Object & Object::operator = (const Object & obj)
{ COCONUT_UNUSED(obj); return *this; }

Object::Object(ClassKind kind) :
	nucleus(ObjectClass, kind)
{ /* NOP */ }

Object::~Object()
{ /* NOP */ }

#pragma mark -

Owning<Any> Object::copyObject(const Any & ref, CopyOption option)
{
	Owning<Any> copy;
	switch (option)
	{
		case CopyMutable:
			copy = ref.mutableCopy();
		break;
		case CopyImmutable:
			copy = ref.copy();
		break;
		case CopyNone:
		case CopyKind:
			copy = ref.kindCopy();
		break;
		default:
			break;
	}
	return copy;
}

Owning<Any> Object::copyObject(const Owning<Any> & ptr, CopyOption option)
{
	if (ptr) {
		if (option == CopyNone) {
			return ptr;
		} else {
			Owning<Any> copy;
			switch (option)
			{
				case CopyMutable:
					copy = ptr->mutableCopy();
				break;
				case CopyImmutable:
					copy = ptr->copy();
				break;
				case CopyKind:
					copy = ptr->kindCopy();
				break;
				default:
					break;
			}
			return copy;
		}
	}
	// Fault();
	return {};
}

#pragma mark -

Owning<Any> Object::valueForKey(const std::string & utf8_key) const
{ return nucleus::valueForKey(utf8_key); }

void Object::setValueForKey(Owning<Any> ptr, const std::string & utf8_key)
{ nucleus::setValueForKey(ptr, utf8_key); }

#pragma mark -

Owning<Any> Object::valueForSelectorKey(const std::string & utf8_selkey, Owning<Any> arg) const
{
	Owning<Any> result;
	if (isSelectorKey(utf8_selkey)) {
		if (arg) {
			if (utf8_selkey == u8"@compare:") {
				result = ptr_create<Number>(compare(*arg));
			} else if (utf8_selkey == u8"@isEqual:") {
				result = ptr_create<Number>(isEqual(*arg));
			} else if (utf8_selkey == u8"@doesContain:") {
				result = ptr_create<Number>(doesContain(*arg));
			} else if (utf8_selkey == u8"@isIdenticalTo:") {
				result = ptr_create<Number>(isIdenticalTo(*arg));
			} else if (utf8_selkey == u8"@isEqualTo:") {
				result = ptr_create<Number>(isEqualTo(*arg));
			} else if (utf8_selkey == u8"@isNotEqualTo:") {
				result = ptr_create<Number>(isNotEqualTo(*arg));
			} else if (utf8_selkey == u8"@isLessThan:") {
				result = ptr_create<Number>(isLessThan(*arg));
			} else if (utf8_selkey == u8"@isLessThanOrEqualTo:") {
				result = ptr_create<Number>(isLessThanOrEqualTo(*arg));
			} else if (utf8_selkey == u8"@isGreaterThan:") {
				result = ptr_create<Number>(isGreaterThan(*arg));
			} else if (utf8_selkey == u8"@isGreaterThanOrEqualTo:") {
				result = ptr_create<Number>(isGreaterThanOrEqualTo(*arg));
			}
		} else {
			std::vector<std::string> parts;
			parts = runtime::algorithm::split<std::string>(utf8_selkey, u8".");
			if (parts.size() >= 2) {
				if (parts[0] == u8"@self") {
					parts.erase(parts.begin());
					result = valueForKeyPath(runtime::algorithm::join<std::string>(parts, u8"."));
				} else if (parts[0] == u8"@sum") {
					parts.erase(parts.begin());
					result = sum(runtime::algorithm::join<std::string>(parts, u8"."));
				} else if (parts[0] == u8"@min") {
					parts.erase(parts.begin());
					result = min(runtime::algorithm::join<std::string>(parts, u8"."));
				} else if (parts[0] == u8"@max") {
					parts.erase(parts.begin());
					result = max(runtime::algorithm::join<std::string>(parts, u8"."));
				} else if (parts[0] == u8"@avg") {
					parts.erase(parts.begin());
					result = avg(runtime::algorithm::join<std::string>(parts, u8"."));
				}else if (parts[0] == u8"@distinctUnionOfObjects") {
					parts.erase(parts.begin());
					result = distinctUnionOfObjects(runtime::algorithm::join<std::string>(parts, u8"."));
				} else if (parts[0] == u8"@unionOfObjects") {
					parts.erase(parts.begin());
					result = unionOfObjects(runtime::algorithm::join<std::string>(parts, u8"."));
				} else if (parts[0] == u8"@distinctUnionOfArrays") {
					parts.erase(parts.begin());
					result = distinctUnionOfArrays(runtime::algorithm::join<std::string>(parts, u8"."));
				} else if (parts[0] == u8"@distinctUnionOfOrderedSets") {
					parts.erase(parts.begin());
					result = distinctUnionOfOrderedSets(runtime::algorithm::join<std::string>(parts, u8"."));
				} else if (parts[0] == u8"@distinctUnionOfSets") {
					parts.erase(parts.begin());
					result = distinctUnionOfSets(runtime::algorithm::join<std::string>(parts, u8"."));
				} else if (parts[0] == u8"@unionOfArrays") {
					parts.erase(parts.begin());
					result = unionOfArrays(runtime::algorithm::join<std::string>(parts, u8"."));
				} else if (parts[0] == u8"@unionOfOrderedSets") {
					parts.erase(parts.begin());
					result = unionOfOrderedSets(runtime::algorithm::join<std::string>(parts, u8"."));
				} else if (parts[0] == u8"@unionOfSets") {
					parts.erase(parts.begin());
					result = unionOfSets(runtime::algorithm::join<std::string>(parts, u8"."));
				}
			} else {
				if (utf8_selkey == u8"@self") {
					result = ptr_snatch<Any>(this);
				} else if (utf8_selkey == u8"@count" || utf8_selkey == u8"@length" || utf8_selkey == u8"@size") {
					result = ptr_create<Number>(size());
				} else if (utf8_selkey == u8"@floatValue") {
					result = ptr_create<Number>(floatValue());
				} else if (utf8_selkey == u8"@doubleValue") {
					result = ptr_create<Number>(doubleValue());
				} else if (utf8_selkey == u8"@boolValue") {
					result = ptr_create<Number>(boolValue());
				} else if (utf8_selkey == u8"@charValue") {
					result = ptr_create<Number>(charValue());
				} else if (utf8_selkey == u8"@shortValue") {
					result = ptr_create<Number>(shortValue());
				} else if (utf8_selkey == u8"@intValue") {
					result = ptr_create<Number>(intValue());
				} else if (utf8_selkey == u8"@longValue") {
					result = ptr_create<Number>(longValue());
				} else if (utf8_selkey == u8"@longLongValue") {
					result = ptr_create<Number>(longLongValue());
				} else if (utf8_selkey == u8"@unsignedCharValue") {
					result = ptr_create<Number>(unsignedCharValue());
				} else if (utf8_selkey == u8"@unsignedShortValue") {
					result = ptr_create<Number>(unsignedShortValue());
				} else if (utf8_selkey == u8"@unsignedIntValue") {
					result = ptr_create<Number>(unsignedIntValue());
				} else if (utf8_selkey == u8"@unsignedLongValue") {
					result = ptr_create<Number>(unsignedLongValue());
				} else if (utf8_selkey == u8"@unsignedLongLongValue") {
					result = ptr_create<Number>(unsignedLongLongValue());
				} else if (utf8_selkey == u8"@stringValue") {
					result = ptr_create<String>(stringValue());
				} else if (utf8_selkey == u8"@description") {
					result = ptr_create<String>(description());
				}
			}
		}
	}
	return result;
}

#pragma mark -

Owning<Any> Object::sum(const std::string & utf8_key) const
{
	double sum = 0.0;
	Owning<Any> v = valueForKeyPath(utf8_key);
	if (v && v->isKindOf(ArrayClass)) {
		auto op = runtime::async::exec(runtime::launch_async, [&v, &sum]
		{
			for (Array::const_iterator it = ptr_static_cast<Array>(v)->cbegin(); it != ptr_static_cast<Array>(v)->cend(); ++it) {
				Owning<Any> vv = (*it);
				if (vv) {
					sum += vv->doubleValue();
				} else {
					// Fault();
				}
			}
		});
		op();
	} else if (v && v->isKindOf(SetClass)) {
		auto op = runtime::async::exec(runtime::launch_async, [&v, &sum]
		{
			for (Set::const_iterator it = ptr_static_cast<Set>(v)->cbegin(); it != ptr_static_cast<Set>(v)->cend(); ++it) {
				Owning<Any> vv = (*it);
				if (vv) {
					sum += vv->doubleValue();
				} else {
					// Fault();
				}
			}
		});
		op();
	} else if (v && v->isKindOf(OrderedSetClass)) {
		auto op = runtime::async::exec(runtime::launch_async, [&v, &sum]
		{
			for (OrderedSet::const_iterator it = ptr_static_cast<OrderedSet>(v)->cbegin(); it != ptr_static_cast<OrderedSet>(v)->cend(); ++it) {
				Owning<Any> vv = (*it);
				if (vv) {
					sum += vv->doubleValue();
				} else {
					// Fault();
				}
			}
		});
		op();
	} else {
		// Fault();
	}
	return ptr_create<Number>(sum);
}

Owning<Any> Object::min(const std::string & utf8_key) const
{
	Owning<Any> min;
	Owning<Any> v = valueForKeyPath(utf8_key);
	if (v && v->isKindOf(ArrayClass)) {
		min = ptr_static_cast<Array>(v)->lastObject();
		if (min) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &min]
			{
				for (Array::const_iterator it = ptr_static_cast<Array>(v)->cbegin(); it != ptr_static_cast<Array>(v)->cend(); ++it) {
					Owning<Any> vv = (*it);
					if (vv) {
						if (OrderedDescending == min->compare(*vv)) {
							min = vv;
						}
					} else {
						// Fault();
					}
				}
			});
			op();
		}
	} else if (v && v->isKindOf(SetClass)) {
		min = ptr_static_cast<Set>(v)->lastObject();
		if (min) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &min]
			{
				for (Set::const_iterator it = ptr_static_cast<Set>(v)->cbegin(); it != ptr_static_cast<Set>(v)->cend(); ++it) {
					Owning<Any> vv = (*it);
					if (vv) {
						if (OrderedDescending == min->compare(*vv)) {
							min = vv;
						}
					} else {
						// Fault();
					}
				}
			});
			op();
		}
	} else if (v && v->isKindOf(OrderedSetClass)) {
		min = ptr_static_cast<OrderedSet>(v)->lastObject();
		if (min) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &min]
			{
				for (OrderedSet::const_iterator it = ptr_static_cast<OrderedSet>(v)->cbegin(); it != ptr_static_cast<OrderedSet>(v)->cend(); ++it) {
					Owning<Any> vv = (*it);
					if (vv) {
						if (OrderedDescending == min->compare(*vv)) {
							min = vv;
						}
					} else {
						// Fault();
					}
				}
			});
			op();
		}
	} else {
		// Fault();
	}
	return min;
}

Owning<Any> Object::max(const std::string & utf8_key) const
{
	Owning<Any> max;
	Owning<Any> v = valueForKeyPath(utf8_key);
	if (v && v->isKindOf(ArrayClass)) {
		max = ptr_static_cast<Array>(v)->lastObject();
		if (max) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &max]
			{
				for (Array::const_iterator it = ptr_static_cast<Array>(v)->cbegin(); it != ptr_static_cast<Array>(v)->cend(); ++it) {
					Owning<Any> vv = (*it);
					if (vv) {
						if (OrderedAscending == max->compare(*vv)) {
							max = vv;
						}
					} else {
						// Fault();
					}
				}
			});
			op();
		}
	} else if (v && v->isKindOf(SetClass)) {
		max = ptr_static_cast<Set>(v)->lastObject();
		if (max) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &max]
			{
				for (Set::const_iterator it = ptr_static_cast<Set>(v)->cbegin(); it != ptr_static_cast<Set>(v)->cend(); ++it) {
					Owning<Any> vv = (*it);
					if (vv) {
						if (OrderedAscending == max->compare(*vv)) {
							max = vv;
						}
					} else {
						// Fault();
					}
				}
			});
			op();
		}
	} else if (v && v->isKindOf(OrderedSetClass)) {
		max = ptr_static_cast<OrderedSet>(v)->lastObject();
		if (max) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &max]
			{
				for (OrderedSet::const_iterator it = ptr_static_cast<OrderedSet>(v)->cbegin(); it != ptr_static_cast<OrderedSet>(v)->cend(); ++it) {
					Owning<Any> vv = (*it);
					if (vv) {
						if (OrderedAscending == max->compare(*vv)) {
							max = vv;
						}
					} else {
						// Fault();
					}
				}
			});
			op();
		}
	} else {
		// Fault();
	}
	return max;
}

Owning<Any> Object::avg(const std::string & utf8_key) const
{
	double avg = 0.0;
	Owning<Any> v = valueForKeyPath(utf8_key);
	if (v && v->isKindOf(ArrayClass)) {
		std::size_t count = ptr_static_cast<Array>(v)->size();
		if (count > 0) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &count, &avg]
			{
				for (Array::const_iterator it = ptr_static_cast<Array>(v)->cbegin(); it != ptr_static_cast<Array>(v)->cend(); ++it) {
					Owning<Any> vv = (*it);
					if (vv) {
						avg += (vv->doubleValue() / static_cast<double>(count));
					} else {
						// Fault();
					}
				}
			});
			op();
		}
	} else if (v && v->isKindOf(SetClass)) {
		std::size_t count = ptr_static_cast<Set>(v)->size();
		if (count > 0) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &count, &avg]
			{
				for (Set::const_iterator it = ptr_static_cast<Set>(v)->cbegin(); it != ptr_static_cast<Set>(v)->cend(); ++it) {
					Owning<Any> vv = (*it);
					if (vv) {
						avg += (vv->doubleValue() / static_cast<double>(count));
					} else {
						// Fault();
					}
				}
			});
			op();
		}
	} else if (v && v->isKindOf(OrderedSetClass)) {
		std::size_t count = ptr_static_cast<OrderedSet>(v)->size();
		if (count > 0) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &count, &avg]
			{
				for (OrderedSet::const_iterator it = ptr_static_cast<OrderedSet>(v)->cbegin(); it != ptr_static_cast<OrderedSet>(v)->cend(); ++it) {
					Owning<Any> vv = (*it);
					if (vv) {
						avg += (vv->doubleValue() / static_cast<double>(count));
					} else {
						// Fault();
					}
				}
			});
			op();
		}
	} else {
		// Fault();
	}
	return ptr_create<Number>(avg);
}

#pragma mark -

Owning<Any> Object::distinctUnionOfObjects(const std::string & utf8_key) const
{
	Owning<Any> v = valueForKeyPath(utf8_key);
	Set::impl_trait buf;
	if (v && v->isKindOf(ArrayClass)) {
		std::size_t count = ptr_static_cast<Array>(v)->size();
		if (count > 0) {
			for (Array::const_iterator it = ptr_static_cast<Array>(v)->cbegin(); it != ptr_static_cast<Array>(v)->cend(); ++it) {
				Owning<Any> vv = (*it);
				if (vv) {
					if (!vv->isMemberOf(NoneClass)) {
						buf.insert(vv);
					} else {
						// Fault();
					}
				} else {
					// Fault();
				}
			}
		}
	} else if (v && v->isKindOf(OrderedSetClass)) {
		std::size_t count = ptr_static_cast<OrderedSet>(v)->size();
		if (count > 0) {
			for (OrderedSet::const_iterator it = ptr_static_cast<OrderedSet>(v)->cbegin(); it != ptr_static_cast<OrderedSet>(v)->cend(); ++it) {
				Owning<Any> vv = (*it);
				if (vv) {
					if (!vv->isMemberOf(NoneClass)) {
						buf.insert(vv);
					} else {
						// Fault();
					}
				} else {
					// Fault();
				}
			}
		}
	} else if (v && v->isKindOf(SetClass)) {
		std::size_t count = ptr_static_cast<Set>(v)->size();
		if (count > 0) {
			for (Set::const_iterator it = ptr_static_cast<Set>(v)->cbegin(); it != ptr_static_cast<Set>(v)->cend(); ++it) {
				Owning<Any> vv = (*it);
				if (vv) {
					if (!vv->isMemberOf(NoneClass)) {
						buf.insert(vv);
					} else {
						// Fault();
					}
				} else {
					// Fault();
				}
			}
		}
	} else {
		// Fault();
	}
	return ptr_create<Array>(buf.begin(), buf.end());
}

Owning<Any> Object::unionOfObjects(const std::string & utf8_key) const
{
	Owning<Any> v = valueForKeyPath(utf8_key);
	Array::impl_trait buf;
	if (v && v->isKindOf(ArrayClass)) {
		std::size_t count = ptr_static_cast<Array>(v)->size();
		if (count > 0) {
			for (Array::const_iterator it = ptr_static_cast<Array>(v)->cbegin(); it != ptr_static_cast<Array>(v)->cend(); ++it) {
				Owning<Any> vv = (*it);
				if (vv) {
					if (!vv->isMemberOf(NoneClass)) {
						buf.push_back(vv);
					} else {
						// Fault();
					}
				} else {
					// Fault();
				}
			}
		}
	} else if (v && v->isKindOf(OrderedSetClass)) {
		std::size_t count = ptr_static_cast<OrderedSet>(v)->size();
		if (count > 0) {
			for (OrderedSet::const_iterator it = ptr_static_cast<OrderedSet>(v)->cbegin(); it != ptr_static_cast<OrderedSet>(v)->cend(); ++it) {
				Owning<Any> vv = (*it);
				if (vv) {
					if (!vv->isMemberOf(NoneClass)) {
						buf.push_back(vv);
					} else {
						// Fault();
					}
				} else {
					// Fault();
				}
			}
		}
	} else if (v && v->isKindOf(SetClass)) {
		std::size_t count = ptr_static_cast<Set>(v)->size();
		if (count > 0) {
			for (Set::const_iterator it = ptr_static_cast<Set>(v)->cbegin(); it != ptr_static_cast<Set>(v)->cend(); ++it) {
				Owning<Any> vv = (*it);
				if (vv) {
					if (!vv->isMemberOf(NoneClass)) {
						buf.push_back(vv);
					} else {
						// Fault();
					}
				} else {
					// Fault();
				}
			}
		}
	} else {
		// Fault();
	}
	return ptr_create<Array>(buf.begin(), buf.end());
}

#pragma mark -

Owning<Any> Object::distinctUnionOfArrays(const std::string & utf8_key) const
{
	Owning<Any> v = valueForKeyPath(utf8_key);
	Set::impl_trait buf;
	if (v && v->isKindOf(ArrayClass)) {
		std::size_t count = ptr_static_cast<Array>(v)->size();
		if (count > 0) {
			for (Array::const_iterator it = ptr_static_cast<Array>(v)->cbegin(); it != ptr_static_cast<Array>(v)->cend(); ++it) {
				Owning<Any> vv = (*it);
				if (vv && vv->isKindOf(ArrayClass)) {
					Owning<Any> vvv = vv->valueForKeyPath(utf8_key);
					if (vvv) {
						if (!vvv->isMemberOf(NoneClass)) {
							buf.insert(vvv);
						} else {
							// Fault();
						}
					} else {
						// Fault();
					}
				} else {
					// Fault();
				}
			}
		}
	} else {
		// Fault();
	}
	return ptr_create<Array>(buf.begin(), buf.end());
}

Owning<Any> Object::distinctUnionOfOrderedSets(const std::string & utf8_key) const
{
	Owning<Any> v = valueForKeyPath(utf8_key);
	OrderedSet::impl_trait buf;
	if (v && v->isKindOf(OrderedSetClass)) {
		std::size_t count = ptr_static_cast<OrderedSet>(v)->size();
		if (count > 0) {
			for (OrderedSet::const_iterator it = ptr_static_cast<OrderedSet>(v)->cbegin(); it != ptr_static_cast<OrderedSet>(v)->cend(); ++it) {
				Owning<Any> vv = (*it);
				if (vv && vv->isKindOf(OrderedSetClass)) {
					Owning<Any> vvv = vv->valueForKeyPath(utf8_key);
					if (vvv) {
						if (!vvv->isMemberOf(NoneClass)) {
							buf.push_back(vvv);
						} else {
							// Fault();
						}
					} else {
						// Fault();
					}
				} else {
					// Fault();
				}
			}
		}
	} else {
		// Fault();
	}
	return ptr_create<OrderedSet>(buf.begin(), buf.end());
}

Owning<Any> Object::distinctUnionOfSets(const std::string & utf8_key) const
{
	Owning<Any> v = valueForKeyPath(utf8_key);
	Set::impl_trait buf;
	if (v && v->isKindOf(SetClass)) {
		std::size_t count = ptr_static_cast<Set>(v)->size();
		if (count > 0) {
			for (Set::const_iterator it = ptr_static_cast<Set>(v)->cbegin(); it != ptr_static_cast<Set>(v)->cend(); ++it) {
				Owning<Any> vv = (*it);
				if (vv && vv->isKindOf(SetClass)) {
					Owning<Any> vvv = vv->valueForKeyPath(utf8_key);
					if (vvv) {
						if (!vvv->isMemberOf(NoneClass)) {
							buf.insert(vvv);
						} else {
							// Fault();
						}
					} else {
						// Fault();
					}
				} else {
					// Fault();
				}
			}
		}
	} else {
		// Fault();
	}
	return ptr_create<Set>(buf.begin(), buf.end());
}

#pragma mark -

Owning<Any> Object::unionOfArrays(const std::string & utf8_key) const
{
	Owning<Any> v = valueForKeyPath(utf8_key);
	Array::impl_trait buf;
	if (v && v->isKindOf(ArrayClass)) {
		std::size_t count = ptr_static_cast<Array>(v)->size();
		if (count > 0) {
			for (Array::const_iterator it = ptr_static_cast<Array>(v)->cbegin(); it != ptr_static_cast<Array>(v)->cend(); ++it) {
				Owning<Any> vv = (*it);
				if (vv && vv->isKindOf(ArrayClass)) {
					Owning<Any> vvv = vv->valueForKeyPath(utf8_key);
					if (vvv) {
						if (!vvv->isMemberOf(NoneClass)) {
							buf.push_back(vvv);
						} else {
							// Fault();
						}
					} else {
						// Fault();
					}
				} else {
					// Fault();
				}
			}
		}
	} else {
		// Fault();
	}
	return  ptr_create<Array>(buf.begin(), buf.end());
}

Owning<Any> Object::unionOfOrderedSets(const std::string & utf8_key) const
{
	Owning<Any> v = valueForKeyPath(utf8_key);
	Array::impl_trait buf;
	if (v && v->isKindOf(OrderedSetClass)) {
		std::size_t count = ptr_static_cast<OrderedSet>(v)->size();
		if (count > 0) {
			for (OrderedSet::const_iterator it = ptr_static_cast<OrderedSet>(v)->cbegin(); it != ptr_static_cast<OrderedSet>(v)->cend(); ++it) {
				Owning<Any> vv = (*it);
				if (vv && vv->isKindOf(OrderedSetClass)) {
					Owning<Any> vvv = vv->valueForKeyPath(utf8_key);
					if (vvv) {
						if (!vvv->isMemberOf(NoneClass)) {
							buf.push_back(vvv);
						} else {
							// Fault();
						}
					} else {
						// Fault();
					}
				} else {
					// Fault();
				}
			}
		}
	} else {
		// Fault();
	}
	return  ptr_create<Array>(buf.begin(), buf.end());
}

Owning<Any> Object::unionOfSets(const std::string & utf8_key) const
{
	Owning<Any> v = valueForKeyPath(utf8_key);
	Array::impl_trait buf;
	if (v && v->isKindOf(SetClass)) {
		std::size_t count = ptr_static_cast<Set>(v)->size();
		if (count > 0) {
			for (Set::const_iterator it = ptr_static_cast<Set>(v)->cbegin(); it != ptr_static_cast<Set>(v)->cend(); ++it) {
				Owning<Any> vv = (*it);
				if (vv && vv->isKindOf(SetClass)) {
					Owning<Any> vvv = vv->valueForKeyPath(utf8_key);
					if (vvv) {
						if (!vvv->isMemberOf(NoneClass)) {
							buf.push_back(vvv);
						} else {
							// Fault();
						}
					} else {
						// Fault();
					}
				} else {
					// Fault();
				}
			}
		}
	} else {
		// Fault();
	}
	return  ptr_create<Array>(buf.begin(), buf.end());
}
	
/* EOF */