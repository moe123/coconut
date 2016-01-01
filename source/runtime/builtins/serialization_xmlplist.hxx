//
// serialization_xmlplist.hxx
//
// Copyright (C) 2015 Cucurbita. All rights reserved.
//

//#define pugi COCONUT_PPCAT(coconut, builtins0pugi)
#define PUGIXML_HEADER_ONLY

namespace coconut
{
	namespace runtime
	{
		namespace builtins
		{
			#include "pugixml.hpp"
			
			struct xmlplist_writer : pugi::xml_writer
			{
				std::string m_buf;
				virtual void write(const void * data, size_t size)
				{ m_buf += std::string(static_cast<const char *>(data), size); }
			};

			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			std::string xmlplist_write_node(const pugi::xml_node & node)
			{
				xmlplist_writer writer;
				node.print(writer);
				return writer.m_buf;
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			Owning<Any> xmlplist_read(const pugi::xml_node & node, SerializationReadOption option);
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			Owning<Any> xmlplist_read_array(const pugi::xml_node & node, SerializationReadOption option)
			{
				std::vector< Owning<Any> > buf;
				for(pugi::xml_node_iterator it = node.begin(); it != node.end(); ++it) {
					pugi::xml_node v = (*it);
					Owning<Any> vv = xmlplist_read(v, option);
					if (vv) { buf.push_back(vv); }
				}
				if (
					option == SerializationReadMutableContainers ||
					option == SerializationReadMutableContainersAndLeaves
				) {
					return MutableArray::with(buf.begin(), buf.end());
				}
				return Array::with(buf.begin(), buf.end());
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			Owning<Any> xmlplist_read_data(const pugi::xml_node & node, SerializationReadOption option)
			{
				std::string val(node.first_child().value());
				if (option == SerializationReadMutableContainersAndLeaves) {
					//return MutableData::with(val.data(), val.size(), true);
				}
				return Data::with(val.data(), val.size(), true);
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			Owning<Any> xmlplist_read_date(const pugi::xml_node & node)
			{
				std::string val(node.first_child().value());
				if (val.size()) {
					return Date::with(Date::fromUTC(val));
				}
				return Date::with(Date::distantPast());
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			Owning<Any> xmlplist_read_dictionary(const pugi::xml_node & node, SerializationReadOption option)
			{
				std::vector< Owning<Any> > kk, vv;
				for(pugi::xml_node_iterator it = node.begin(); it != node.end(); ++it) {
					if(std::string("key") != it->name()) {
						throw std::invalid_argument("coconut parsing xmlplist");
					}
					std::string key(it->first_child().value());
					++it;
					if(it == node.end()) {
						throw std::invalid_argument("coconut parsing xmlplist");
					} else if(std::string("key") == std::string(it->name())) {
						throw std::invalid_argument("coconut parsing xmlplist");
					}
					Owning<Any> k = String::with(key);
					Owning<Any> v = xmlplist_read(*it, option);
					if (k && v) {
						kk.push_back(v);
						vv.push_back(k);
					}
				}
				if (
					option == SerializationReadMutableContainers ||
					option == SerializationReadMutableContainersAndLeaves
				) {
					return MutableDictionary::with(kk.begin(), kk.end(), vv.begin(), vv.end());
				}
				return Dictionary::with(kk.begin(), kk.end(), vv.begin(), vv.end());
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			Owning<Any> xmlplist_read_number(const pugi::xml_node & node)
			{
				std::string type = node.name();
				if("false" == type) {
					return Number::with(false);
				} else if("true" == type) {
					return Number::with(true);
				} else if("integer" == type) {
					std::string val = node.first_child().value();
					return Number::with(runtime::algorithm::to_numeric<std::int64_t>(val));
				} else if("real" == type) {
					std::string val = node.first_child().value();
					return Number::with(runtime::algorithm::to_numeric<double>(val));
				}
				return Number::with(NotFound);
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			Owning<Any> xmlplist_read_string(const pugi::xml_node & node, SerializationReadOption option)
			{
				std::string val(node.first_child().value());
				if (option == SerializationReadMutableContainersAndLeaves) {
					//return MutableString::with(val);
				}
				return String::with(val);
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			Owning<Any> xmlplist_read(const pugi::xml_node & node, SerializationReadOption option)
			{
				std::string type(node.name());
				
				if("dict" == type) {
					return xmlplist_read_dictionary(node, option);
				} else if("array" == type) {
					return xmlplist_read_array(node, option);
				} else if("string" == type) {
					return xmlplist_read_string(node, option);
				} else if("integer" == type || "real" == type || "false" == type || "true" == type) {
					return xmlplist_read_number(node);
				} else if("data" == type) {
					return xmlplist_read_data(node, option);
				} else if("date" == type) {
					return xmlplist_read_date(node);
				} else {
					throw std::invalid_argument("coconut parsing xmlplist");
				}
				return {};
			}
			
			COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
			Owning<Any> xmlplist_from_raw(const std::uint8_t * in, std::size_t len, SerializationReadOption option)
			{
				try {
					pugi::xml_document document;
				#ifdef PUGIXML_WCHAR_MODE
					#error PUGIXML_WCHAR_MODE
				#else
					pugi::xml_parse_result result = document.load_buffer(
						unsafe_cast<const char *>(in),
						len,
						pugi::parse_default,
						pugi::encoding_utf8
					);
				#endif
					if(result) {
						pugi::xml_node tree = document.child("plist").first_child();
						return xmlplist_read(tree, option);
					}
				} catch (...) { /**/ }
				return {};
			}
		}
	}
}

/* EOF */