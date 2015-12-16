//
// Object.cpp
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

#include <coconut/runtime/Object.hpp>
#include <coconut/foundation/Array.hpp>
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

kind_ptr Object::copyObject(const_kind_ref ref, CopyOption option)
{
	kind_ptr copy;
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

kind_ptr Object::copyObject(const_kind_ptr & ptr, CopyOption option)
{
	if (ptr) {
		if (option == CopyNone) {
			return ptr;
		} else {
			kind_ptr copy;
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

kind_ptr Object::valueForKey(const std::string & utf8_key) const
{ return nucleus::valueForKey(utf8_key); }

void Object::setValueForKey(kind_ptr ptr, const std::string & utf8_key)
{ nucleus::setValueForKey(ptr, utf8_key); }

#pragma mark -

kind_ptr Object::valueForSelectorKey(const std::string & utf8_selkey, kind_ptr arg) const
{
	kind_ptr result;
	if (isSelectorKey(utf8_selkey)) {
		if (arg) {
			if (utf8_selkey == u8"@isEqual:") {
				result = Number::with(isEqual(*arg));
			} else if (utf8_selkey == u8"@compare:") {
				result = Number::with(compare(*arg));
			} else if (utf8_selkey == u8"@doesContain:") {
				result = Number::with(doesContain(*arg));
			} else if (utf8_selkey == u8"@isIdenticalTo:") {
				result = Number::with(isIdenticalTo(*arg));
			} else if (utf8_selkey == u8"@isEqualTo:") {
				result = Number::with(isEqualTo(*arg));
			} else if (utf8_selkey == u8"@isNotEqualTo:") {
				result = Number::with(isNotEqualTo(*arg));
			} else if (utf8_selkey == u8"@isLessThan:") {
				result = Number::with(isLessThan(*arg));
			} else if (utf8_selkey == u8"@isLessThanOrEqualTo:") {
				result = Number::with(isLessThanOrEqualTo(*arg));
			} else if (utf8_selkey == u8"@isGreaterThan:") {
				result = Number::with(isGreaterThan(*arg));
			} else if (utf8_selkey == u8"@isGreaterThanOrEqualTo:") {
				result = Number::with(isGreaterThanOrEqualTo(*arg));
			}
		} else {
			std::vector<std::string> parts;
			parts = runtime::algorithm::split<std::string>(utf8_selkey, u8".");
			if (parts.size() >= 2) {
				if(parts[0] == u8"@sum") {
					parts.erase(parts.begin());
					result = sum(runtime::algorithm::join<std::string>(parts, u8"."));
				} else if(parts[0] == u8"@min") {
					parts.erase(parts.begin());
					result = min(runtime::algorithm::join<std::string>(parts, u8"."));
				} else if(parts[0] == u8"@max") {
					parts.erase(parts.begin());
					result = max(runtime::algorithm::join<std::string>(parts, u8"."));
				} else if(parts[0] == u8"@avg") {
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
				if (utf8_selkey == u8"@count" || utf8_selkey == u8"@length" || utf8_selkey == u8"@size") {
					result = Number::with(size());
				} else if (utf8_selkey == u8"@floatValue") {
					result = Number::with(floatValue());
				} else if (utf8_selkey == u8"@doubleValue") {
					result = Number::with(doubleValue());
				} else if (utf8_selkey == u8"@boolValue") {
					result = Number::with(boolValue());
				} else if (utf8_selkey == u8"@charValue") {
					result = Number::with(charValue());
				} else if (utf8_selkey == u8"@shortValue") {
					result = Number::with(shortValue());
				} else if (utf8_selkey == u8"@intValue") {
					result = Number::with(intValue());
				} else if (utf8_selkey == u8"@longValue") {
					result = Number::with(longValue());
				} else if (utf8_selkey == u8"@longLongValue") {
					result = Number::with(longLongValue());
				} else if (utf8_selkey == u8"@unsignedCharValue") {
					result = Number::with(unsignedCharValue());
				} else if (utf8_selkey == u8"@unsignedShortValue") {
					result = Number::with(unsignedShortValue());
				} else if (utf8_selkey == u8"@unsignedIntValue") {
					result = Number::with(unsignedIntValue());
				} else if (utf8_selkey == u8"@unsignedLongValue") {
					result = Number::with(unsignedLongValue());
				} else if (utf8_selkey == u8"@unsignedLongLongValue") {
					result = Number::with(unsignedLongLongValue());
				} else if (utf8_selkey == u8"@stringValue") {
					result = String::with(stringValue());
				} else if (utf8_selkey == u8"@description") {
					result = String::with(description());
				}
			}
		}
	}
	return result;
}

#pragma mark -

kind_ptr Object::sum(const std::string & utf8_key) const
{
	double sum = 0.0;
	kind_ptr v = valueForKeyPath(utf8_key);
	if (v && v->isKindOf(ArrayClass)) {
		auto op = runtime::async::exec(runtime::launch_async, [&v, &sum]
		{
			for (Array::const_iterator it = ptr_static_cast<Array>(v)->cbegin(); it != ptr_static_cast<Array>(v)->cend(); ++it) {
				kind_ptr vv = (*it);
				if (vv) {
					sum += vv->doubleValue();
				} else {
					// Fault();
				}
			}
		});
		op.get();
	} else if (v && v->isKindOf(SetClass)) {
		auto op = runtime::async::exec(runtime::launch_async, [&v, &sum]
		{
			for (Set::const_iterator it = ptr_static_cast<Set>(v)->cbegin(); it != ptr_static_cast<Set>(v)->cend(); ++it) {
				kind_ptr vv = (*it);
				if (vv) {
					sum += vv->doubleValue();
				} else {
					// Fault();
				}
			}
		});
		op.get();
	} else if (v && v->isKindOf(OrderedSetClass)) {
		auto op = runtime::async::exec(runtime::launch_async, [&v, &sum]
		{
			for (OrderedSet::const_iterator it = ptr_static_cast<OrderedSet>(v)->cbegin(); it != ptr_static_cast<OrderedSet>(v)->cend(); ++it) {
				kind_ptr vv = (*it);
				if (vv) {
					sum += vv->doubleValue();
				} else {
					// Fault();
				}
			}
		});
		op.get();
	} else {
		// Fault();
	}
	return Number::with(sum);
}

kind_ptr Object::min(const std::string & utf8_key) const
{
	kind_ptr min;
	kind_ptr v = valueForKeyPath(utf8_key);
	if (v && v->isKindOf(ArrayClass)) {
		min = ptr_static_cast<Array>(v)->lastObject();
		if (min) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &min]
			{
				for (Array::const_iterator it = ptr_static_cast<Array>(v)->cbegin(); it != ptr_static_cast<Array>(v)->cend(); ++it) {
					kind_ptr vv = (*it);
					if (vv) {
						if (OrderedDescending == min->compare(*vv)) {
							min = vv;
						}
					} else {
						// Fault();
					}
				}
			});
			op.get();
		}
	} else if (v && v->isKindOf(SetClass)) {
		min = ptr_static_cast<Set>(v)->lastObject();
		if (min) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &min]
			{
				for (Set::const_iterator it = ptr_static_cast<Set>(v)->cbegin(); it != ptr_static_cast<Set>(v)->cend(); ++it) {
					kind_ptr vv = (*it);
					if (vv) {
						if (OrderedDescending == min->compare(*vv)) {
							min = vv;
						}
					} else {
						// Fault();
					}
				}
			});
			op.get();
		}
	} else if (v && v->isKindOf(OrderedSetClass)) {
		min = ptr_static_cast<OrderedSet>(v)->lastObject();
		if (min) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &min]
			{
				for (OrderedSet::const_iterator it = ptr_static_cast<OrderedSet>(v)->cbegin(); it != ptr_static_cast<OrderedSet>(v)->cend(); ++it) {
					kind_ptr vv = (*it);
					if (vv) {
						if (OrderedDescending == min->compare(*vv)) {
							min = vv;
						}
					} else {
						// Fault();
					}
				}
			});
			op.get();
		}
	} else {
		// Fault();
	}
	return min;
}

kind_ptr Object::max(const std::string & utf8_key) const
{
	kind_ptr max;
	kind_ptr v = valueForKeyPath(utf8_key);
	if (v && v->isKindOf(ArrayClass)) {
		max = ptr_static_cast<Array>(v)->lastObject();
		if (max) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &max]
			{
				for (Array::const_iterator it = ptr_static_cast<Array>(v)->cbegin(); it != ptr_static_cast<Array>(v)->cend(); ++it) {
					kind_ptr vv = (*it);
					if (vv) {
						if (OrderedAscending == max->compare(*vv)) {
							max = vv;
						}
					} else {
						// Fault();
					}
				}
			});
			op.get();
		}
	} else if (v && v->isKindOf(SetClass)) {
		max = ptr_static_cast<Set>(v)->lastObject();
		if (max) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &max]
			{
				for (Set::const_iterator it = ptr_static_cast<Set>(v)->cbegin(); it != ptr_static_cast<Set>(v)->cend(); ++it) {
					kind_ptr vv = (*it);
					if (vv) {
						if (OrderedAscending == max->compare(*vv)) {
							max = vv;
						}
					} else {
						// Fault();
					}
				}
			});
			op.get();
		}
	} else if (v && v->isKindOf(OrderedSetClass)) {
		max = ptr_static_cast<OrderedSet>(v)->lastObject();
		if (max) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &max]
			{
				for (OrderedSet::const_iterator it = ptr_static_cast<OrderedSet>(v)->cbegin(); it != ptr_static_cast<OrderedSet>(v)->cend(); ++it) {
					kind_ptr vv = (*it);
					if (vv) {
						if (OrderedAscending == max->compare(*vv)) {
							max = vv;
						}
					} else {
						// Fault();
					}
				}
			});
			op.get();
		}
	} else {
		// Fault();
	}
	return max;
}

kind_ptr Object::avg(const std::string & utf8_key) const
{
	double avg = 0.0;
	kind_ptr v = valueForKeyPath(utf8_key);
	if (v && v->isKindOf(ArrayClass)) {
		std::size_t count = ptr_static_cast<Array>(v)->size();
		if (count > 0) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &count, &avg]
			{
				for (Array::const_iterator it = ptr_static_cast<Array>(v)->cbegin(); it != ptr_static_cast<Array>(v)->cend(); ++it) {
					kind_ptr vv = (*it);
					if (vv) {
						avg += (vv->doubleValue() / static_cast<double>(count));
					} else {
						// Fault();
					}
				}
			});
			op.get();
		}
	} else if (v && v->isKindOf(SetClass)) {
		std::size_t count = ptr_static_cast<Set>(v)->size();
		if (count > 0) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &count, &avg]
			{
				for (Set::const_iterator it = ptr_static_cast<Set>(v)->cbegin(); it != ptr_static_cast<Set>(v)->cend(); ++it) {
					kind_ptr vv = (*it);
					if (vv) {
						avg += (vv->doubleValue() / static_cast<double>(count));
					} else {
						// Fault();
					}
				}
			});
			op.get();
		}
	} else if (v && v->isKindOf(OrderedSetClass)) {
		std::size_t count = ptr_static_cast<OrderedSet>(v)->size();
		if (count > 0) {
			auto op = runtime::async::exec(runtime::launch_async, [&v, &count, &avg]
			{
				for (OrderedSet::const_iterator it = ptr_static_cast<OrderedSet>(v)->cbegin(); it != ptr_static_cast<OrderedSet>(v)->cend(); ++it) {
					kind_ptr vv = (*it);
					if (vv) {
						avg += (vv->doubleValue() / static_cast<double>(count));
					} else {
						// Fault();
					}
				}
			});
			op.get();
		}
	} else {
		// Fault();
	}
	return Number::with(avg);
}

#pragma mark -

kind_ptr Object::distinctUnionOfObjects(const std::string & utf8_key) const
{
	kind_ptr v = valueForKeyPath(utf8_key);
	Set::impl_type buf;
	if (v && v->isKindOf(ArrayClass)) {
		std::size_t count = ptr_static_cast<Array>(v)->size();
		if (count > 0) {
			for (Array::const_iterator it = ptr_static_cast<Array>(v)->cbegin(); it != ptr_static_cast<Array>(v)->cend(); ++it) {
				kind_ptr vv = (*it);
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
				kind_ptr vv = (*it);
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
				kind_ptr vv = (*it);
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
	return Array::with(buf.begin(), buf.end());
}

kind_ptr Object::unionOfObjects(const std::string & utf8_key) const
{
	kind_ptr v = valueForKeyPath(utf8_key);
	Array::impl_type buf;
	if (v && v->isKindOf(ArrayClass)) {
		std::size_t count = ptr_static_cast<Array>(v)->size();
		if (count > 0) {
			for (Array::const_iterator it = ptr_static_cast<Array>(v)->cbegin(); it != ptr_static_cast<Array>(v)->cend(); ++it) {
				kind_ptr vv = (*it);
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
				kind_ptr vv = (*it);
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
				kind_ptr vv = (*it);
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
	return Array::with(buf.begin(), buf.end());
}

#pragma mark -

kind_ptr Object::distinctUnionOfArrays(const std::string & utf8_key) const
{
	kind_ptr v = valueForKeyPath(utf8_key);
	Set::impl_type buf;
	if (v && v->isKindOf(ArrayClass)) {
		std::size_t count = ptr_static_cast<Array>(v)->size();
		if (count > 0) {
			for (Array::const_iterator it = ptr_static_cast<Array>(v)->cbegin(); it != ptr_static_cast<Array>(v)->cend(); ++it) {
				kind_ptr vv = (*it);
				if (vv && vv->isKindOf(ArrayClass)) {
					kind_ptr vvv = vv->valueForKeyPath(utf8_key);
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
	return Array::with(buf.begin(), buf.end());
}

kind_ptr Object::distinctUnionOfOrderedSets(const std::string & utf8_key) const
{
	kind_ptr v = valueForKeyPath(utf8_key);
	OrderedSet::impl_type buf;
	if (v && v->isKindOf(OrderedSetClass)) {
		std::size_t count = ptr_static_cast<OrderedSet>(v)->size();
		if (count > 0) {
			for (OrderedSet::const_iterator it = ptr_static_cast<OrderedSet>(v)->cbegin(); it != ptr_static_cast<OrderedSet>(v)->cend(); ++it) {
				kind_ptr vv = (*it);
				if (vv && vv->isKindOf(OrderedSetClass)) {
					kind_ptr vvv = vv->valueForKeyPath(utf8_key);
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
	return OrderedSet::with(buf.begin(), buf.end());
}

kind_ptr Object::distinctUnionOfSets(const std::string & utf8_key) const
{
	kind_ptr v = valueForKeyPath(utf8_key);
	Set::impl_type buf;
	if (v && v->isKindOf(SetClass)) {
		std::size_t count = ptr_static_cast<Set>(v)->size();
		if (count > 0) {
			for (Set::const_iterator it = ptr_static_cast<Set>(v)->cbegin(); it != ptr_static_cast<Set>(v)->cend(); ++it) {
				kind_ptr vv = (*it);
				if (vv && vv->isKindOf(SetClass)) {
					kind_ptr vvv = vv->valueForKeyPath(utf8_key);
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
	return Set::with(buf.begin(), buf.end());
}

#pragma mark -

kind_ptr Object::unionOfArrays(const std::string & utf8_key) const
{
	kind_ptr v = valueForKeyPath(utf8_key);
	Array::impl_type buf;
	if (v && v->isKindOf(ArrayClass)) {
		std::size_t count = ptr_static_cast<Array>(v)->size();
		if (count > 0) {
			for (Array::const_iterator it = ptr_static_cast<Array>(v)->cbegin(); it != ptr_static_cast<Array>(v)->cend(); ++it) {
				kind_ptr vv = (*it);
				if (vv && vv->isKindOf(ArrayClass)) {
					kind_ptr vvv = vv->valueForKeyPath(utf8_key);
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
	return Array::with(buf.begin(), buf.end());
}

kind_ptr Object::unionOfOrderedSets(const std::string & utf8_key) const
{
	kind_ptr v = valueForKeyPath(utf8_key);
	Array::impl_type buf;
	if (v && v->isKindOf(OrderedSetClass)) {
		std::size_t count = ptr_static_cast<OrderedSet>(v)->size();
		if (count > 0) {
			for (OrderedSet::const_iterator it = ptr_static_cast<OrderedSet>(v)->cbegin(); it != ptr_static_cast<OrderedSet>(v)->cend(); ++it) {
				kind_ptr vv = (*it);
				if (vv && vv->isKindOf(OrderedSetClass)) {
					kind_ptr vvv = vv->valueForKeyPath(utf8_key);
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
	return Array::with(buf.begin(), buf.end());
}

kind_ptr Object::unionOfSets(const std::string & utf8_key) const
{
	kind_ptr v = valueForKeyPath(utf8_key);
	Array::impl_type buf;
	if (v && v->isKindOf(SetClass)) {
		std::size_t count = ptr_static_cast<Set>(v)->size();
		if (count > 0) {
			for (Set::const_iterator it = ptr_static_cast<Set>(v)->cbegin(); it != ptr_static_cast<Set>(v)->cend(); ++it) {
				kind_ptr vv = (*it);
				if (vv && vv->isKindOf(SetClass)) {
					kind_ptr vvv = vv->valueForKeyPath(utf8_key);
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
	return Array::with(buf.begin(), buf.end());
}
	
/* EOF */