//
// nutrt-uri_joining.hxx
//
// Copyright (C) 2015-2016 Cucurbita. All rights reserved.
//

namespace coconut
{ namespace runtime
{ namespace builtins
{

___COCONUT_BEGIN_DECLS
#include "uriparser/Uri.h"
___COCONUT_END_DECLS

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool uri_join(
	const std::string & relative
	, const std::string & base
	, std::string & out
	, bool normalize
) {
	bool result = false;
	UriParserStateA state;
	UriUriA uriOne;
	UriUriA uriTwo;
	UriUriA uriJoin;

	state.uri = &uriOne;
	if (uriParseUriA(&state, base.c_str()) != URI_SUCCESS) {
		uriFreeUriMembersA(&uriOne);
		return result;
	}

	state.uri = &uriTwo;
	if (uriParseUriA(&state, relative.c_str()) != URI_SUCCESS) {
		uriFreeUriMembersA(&uriTwo);
		return result;
	}

	if (uriAddBaseUriA(&uriJoin, &uriTwo, &uriOne) != URI_SUCCESS) {
		uriFreeUriMembersA(&uriOne);
		uriFreeUriMembersA(&uriTwo);
		uriFreeUriMembersA(&uriJoin);
		return result;
	}

	if (normalize) {
		uriNormalizeSyntaxA(&uriJoin);
	}

	uriFreeUriMembersA(&uriOne);
	uriFreeUriMembersA(&uriTwo);

	int alloc_size;
	uriToStringCharsRequiredA(&uriJoin, &alloc_size);
	alloc_size++;

	std::vector<char> vecbuf(static_cast<std::size_t>(alloc_size));
	if (uriToStringA(vecbuf.data(), &uriJoin, alloc_size, NULL) != URI_SUCCESS) {
		uriFreeUriMembersA(&uriJoin);
		return result;
	}

	if (vecbuf.size()) {
		out.assign(vecbuf.data());
		if (out.back() == '\0') { out.pop_back(); }
		result = true;
	}
	uriFreeUriMembersA(&uriJoin);

	return result;
}

}}} /* EONS */

/* EOF */