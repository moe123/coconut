//
// nutrt-uri_parsing.hxx
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

namespace
{

static struct { const char * scheme; } const uri_schemes[] =
{
	// IANA permanent
	"aaa", "aaas", "about", "acap", "acct", "cap", "cid", "coap", "coaps", "crid",
	"data", "dav", "dict", "dns", "file", "ftp", "geo", "go", "gopher", "h323",
	"http", "https", "iax", "icap", "im", "imap", "info", "ipp", "ipps", "iris",
	"iris.beep", "iris.xpc", "iris.xpcs", "iris.lwz", "jabber", "ldap", "mailto",
	"mid", "msrp", "msrps", "mtqp", "mupdate", "news", "nfs", "ni", "nih", "nntp",
	"opaquelocktoken", "pkcs11", "pop", "pres", "reload", "rtsp", "rtsps", "rtspu",
	"service", "session", "shttp", "sieve", "sip", "sips", "sms", "snmp", "soap.beep",
	"soap.beeps", "stun", "stuns", "tag", "tel", "telnet", "tftp", "thismessage",
	"tn3270", "tip", "turn", "turns", "tv", "urn", "vemmi", "ws", "wss", "xcon",
	"xcon-userid", "xmlrpc.beep", "xmlrpc.beeps", "xmpp", "z39.50r", "z39.50s",
	
	// IANA permanent upper-case
	"AAA", "AAAS", "ABOUT", "ACAP", "ACCT", "CAP", "CID", "COAP", "COAPS", "CRID",
	"DATA", "DAV", "DICT", "DNS", "FILE", "FTP", "GEO", "GO", "GOPHER", "H323",
	"HTTP", "HTTPS", "IAX", "ICAP", "IM", "IMAP", "INFO", "IPP", "IPPS", "IRIS",
	"IRIS.BEEP", "IRIS.XPC", "IRIS.XPCS", "IRIS.LWZ", "JABBER", "LDAP", "MAILTO",
	"MID", "MSRP", "MSRPS", "MTQP", "MUPDATE", "NEWS", "NFS", "NI", "NIH", "NNTP",
	"OPAQUELOCKTOKEN", "PKCS11", "POP", "PRES", "RELOAD", "RTSP", "RTSPS", "RTSPU",
	"SERVICE", "SESSION", "SHTTP", "SIEVE", "SIP", "SIPS", "SMS", "SNMP", "SOAP.BEEP",
	"SOAP.BEEPS", "STUN", "STUNS", "TAG", "TEL", "TELNET", "TFTP", "THISMESSAGE",
	"TN3270", "TIP", "TURN", "TURNS", "TV", "URN", "VEMMI", "WS", "WSS", "XCON",
	"XCON-USERID", "XMLRPC.BEEP", "XMLRPC.BEEPS", "XMPP", "Z39.50R", "Z39.50S",
	
	// IANA provisional
	"acr", "adiumxtra", "afp", "afs", "aim", "apt", "attachment", "aw", "barion",
	"beshare", "bitcoin", "bolo", "callto", "chrome", "chrome-extension",
	"com-eventbrite-attendee", "content", "cvs", "dlna-playsingle", "dlna-playcontainer",
	"dtn", "dvb", "ed2k", "facetime", "feed", "feedready", "finger", "fish", "gg", "git",
	"gizmoproject", "gtalk", "ham", "hcp", "icon", "ipn", "irc", "irc6", "ircs", "itms",
	"jar", "jms", "keyparc", "lastfm", "ldaps", "magnet", "maps", "market", "message",
	"mms", "ms-help", "ms-settings-power", "msnim", "mumble", "mvn", "notes", "oid",
	"palm", "paparazzi", "platform", "proxy", "psyc", "query", "res", "resource", "rmi",
	"rsync", "rtmfp", "rtmp", "secondlife", "sftp", "sgn", "skype", "smb", "smtp",
	"soldat", "spotify", "ssh", "steam", "submit", "svn", "teamspeak", "teliaeid",
	"things", "udp", "unreal", "ut2004", "ventrilo", "view-source", "webcal", "wtai",
	"wyciwyg", "xfire", "xri", "ymsgr",
	
	// IANA provisional upper-case
	"ACR", "ADIUMXTRA", "AFP", "AFS", "AIM", "APT", "ATTACHMENT", "AW", "BARION",
	"BESHARE", "BITCOIN", "BOLO", "CALLTO", "CHROME", "CHROME-EXTENSION",
	"COM-EVENTBRITE-ATTENDEE", "CONTENT", "CVS", "DLNA-PLAYSINGLE", "DLNA-PLAYCONTAINER",
	"DTN", "DVB", "ED2K", "FACETIME", "FEED", "FEEDREADY", "FINGER", "FISH", "GG", "GIT",
	"GIZMOPROJECT", "GTALK", "HAM", "HCP", "ICON", "IPN", "IRC", "IRC6", "IRCS", "ITMS",
	"JAR", "JMS", "KEYPARC", "LASTFM", "LDAPS", "MAGNET", "MAPS", "MARKET", "MESSAGE",
	"MMS", "MS-HELP", "MS-SETTINGS-POWER", "MSNIM", "MUMBLE", "MVN", "NOTES", "OID",
	"PALM", "PAPARAZZI", "PLATFORM", "PROXY", "PSYC", "QUERY", "RES", "RESOURCE", "RMI",
	"RSYNC", "RTMFP", "RTMP", "SECONDLIFE", "SFTP", "SGN", "SKYPE", "SMB", "SMTP",
	"SOLDAT", "SPOTIFY", "SSH", "STEAM", "SUBMIT", "SVN", "TEAMSPEAK", "TELIAEID",
	"THINGS", "UDP", "UNREAL", "UT2004", "VENTRILO", "VIEW-SOURCE", "WEBCAL", "WTAI",
	"WYCIWYG", "XFIRE", "XRI", "YMSGR",
	
	// EOS
	nullptr
};
	
} /* EONS */

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool uri_valid_scheme(const std::string & scheme)
{
	std::size_t i = 0;
	do {
		if (std::string(uri_schemes[i].scheme) == scheme) {
			return true;
		}
		++i;
	} while(nullptr != uri_schemes[i].scheme);
	return false;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool uri_have_scheme(const std::string & in)
{
	std::size_t i = 0;
	do {
		if (algorithms::starts_with(in, std::string(uri_schemes[i].scheme) + "://")) {
			return true;
		}
		++i;
	} while(nullptr != uri_schemes[i].scheme);
	return false;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool uri_filetouri(const std::string & in, std::string & out)
{
	std::vector<char> vecbuf(1152);
	int (*filenameToUriString)(const char *, char *);
	if (in.size() > 2 &&
		((algorithms::is_alpha(in[0]) && in[1] == ':') ||
		 std::string::npos != in.find_first_of("\\"))
		) {
		filenameToUriString = &uriWindowsFilenameToUriStringA;
	} else {
		filenameToUriString = &uriUnixFilenameToUriStringA;
	}
	if (URI_SUCCESS == filenameToUriString(in.c_str(), vecbuf.data())) {
		out.assign(vecbuf.data());
		if (out.back() == '\0') { out.pop_back(); }
		return true;
	}
	return false;
}

COCONUT_PRIVATE COCONUT_ALWAYS_INLINE
bool uri_parse(
	const std::string & in,
	std::map<std::string, std::string> & out_map,
	std::map<std::string, std::string> & out_params,
	bool & is_file,
	std::uint16_t & port,
	bool normalize)
{
	bool result = false;
	UriParserStateA uri_state;
	UriUriA uri_parse;
	std::string buf;
	std::vector<char> vecbuf;

	uri_state.uri = &uri_parse;

	if (URI_SUCCESS == uriParseUriA(&uri_state, in.c_str())) {
		#define COCONUT_URI_CPY_RANGE(OUT, RG) \
			if (RG.first && RG.afterLast) { \
				OUT.assign(RG.first, RG.afterLast); \
				if (OUT.back() == '\0') { OUT.pop_back(); } \
			}

		#define COCONUT_URI_CPY_PATH(OUT, HEAD) \
		{ \
			UriPathSegmentStructA * h(HEAD); \
			std::string seg; \
			const std::string sep("/"); \
			while (h) { \
				COCONUT_URI_CPY_RANGE(seg, h->text) \
				{ \
					OUT += sep + seg; \
					seg.clear(); \
				} \
				h = h->next; \
			} \
		}

		#define COCONUT_URI_CPY_QUERY_PARAMS(OUT, RG) \
		{ \
			UriQueryListA * h; \
			int cnt; \
			if (URI_SUCCESS == uriDissectQueryMallocA(&h, &cnt, RG.first, RG.afterLast)) { \
				while (h) { \
					OUT.insert( \
						std::pair<std::string, std::string>(h->key, h->value == NULL ? "" : h->value) \
					); \
					h = h->next; \
				} \
			} \
			uriFreeQueryListA(h); \
		}

		if (normalize) {
			uriNormalizeSyntaxA(&uri_parse);
		}

		COCONUT_URI_CPY_RANGE(out_map.at("scheme"), uri_parse.scheme)
		if (out_map.at("scheme").size()) {
			result = uri_valid_scheme(out_map.at("scheme"));
		}

		if (!result) {
			out_map.at("scheme").clear();
			uriFreeUriMembersA(&uri_parse);
			return result;
		}

		if (algorithms::icmp(out_map.at("scheme"), "file") == cmp_same) {
			is_file = true;
		}

		COCONUT_URI_CPY_RANGE(out_map.at("host"), uri_parse.hostText)
		COCONUT_URI_CPY_RANGE(buf, uri_parse.userInfo)
		if (buf.size()) {
			if (std::string::npos != buf.find_first_of(":")) {
				std::vector<std::string> out;
				algorithms::explode(out, ":", buf, 2);
				if (out.size() == 2) {
					out_map.at("user").assign(out[0]);
					out_map.at("password").assign(out[1]);
				} else if (out.size() == 1) {
					out_map.at("user").assign(out[0]);
				} else {
					out_map.at("user").assign(buf);
				}
			} else {
				out_map.at("user").assign(buf);
			}
			buf.clear();
		}

		COCONUT_URI_CPY_PATH(buf, uri_parse.pathHead)
		if (buf.size()) {
			std::size_t found = buf.find_first_of(";");
			if (std::string::npos != found) {
				out_map.at("path").assign(buf.begin(), buf.begin() + static_cast<std::string::difference_type>(found));
				if (buf.size() > found) {
					out_map.at("parameter").assign(buf.begin() + (static_cast<std::string::difference_type>(found) + 1), buf.end());
				}
			} else {
				out_map.at("path").assign(buf);
			}
			buf.clear();
		}

		COCONUT_URI_CPY_RANGE(out_map.at("query"), uri_parse.query)
		if (out_map.at("query").size()) {
			COCONUT_URI_CPY_QUERY_PARAMS(out_params, uri_parse.query);
		}
		COCONUT_URI_CPY_RANGE(out_map.at("fragment"), uri_parse.fragment)
		COCONUT_URI_CPY_RANGE(buf, uri_parse.portText)
		if (buf.size()) {
			port = algorithms::to_numeric<std::size_t>(buf);
			if (port > 0 && port < 65535) {
				out_map.at("port").assign(buf);
			}
			buf.clear();
		}

		#undef COCONUT_URI_CPY_QUERY_PARAMS
		#undef COCONUT_URI_CPY_PATH
		#undef COCONUT_URI_CPY_RANGE

		out_map.at("specifier") = "//";

		if (out_map.at("user").size()) {
			out_map.at("specifier") += out_map.at("user");
			/*
			vecbuf.assign(out_map.at("user").begin(), out_map.at("user").end());
			vecbuf.push_back('\0');
			if (uriUnescapeInPlaceA(vecbuf.data())) {
				out_map.at("user").assign(vecbuf.data());
			}
			vecbuf.clear();
			*/
			if (out_map.at("password").size()) {
				out_map.at("specifier") += ":";
				out_map.at("specifier") += out_map.at("password");
				/*
				vecbuf.assign(out_map.at("password").begin(), out_map.at("password").end());
				vecbuf.push_back('\0');
				if (uriUnescapeInPlaceA(vecbuf.data())) {
					out_map.at("password").assign(vecbuf.data());
				}
				vecbuf.clear();
				*/
			}
			out_map.at("specifier") += "@";
		}
		if (!out_map.at("host").size()) {
			out_map.at("host") = "localhost";
		}
		out_map.at("specifier") += out_map.at("host");
		
		if (out_map.at("port").size()) {
			out_map.at("specifier") += ":";
			out_map.at("specifier") += out_map.at("port");
		}
		if (out_map.at("path").size()) {
			out_map.at("specifier") += out_map.at("path");
			if (is_file) {
				vecbuf.resize(out_map.at("path").size() + 1);
				if (URI_SUCCESS == uriUriStringToUnixFilenameA(out_map.at("path").c_str(), vecbuf.data())) {
					out_map.at("path").assign(vecbuf.data());
				}
				vecbuf.clear();
			}

		}
		/* else {
			if (out_map.at("parameter").size() || out_map.at("query").size() || out_map.at("fragment").size()) {
				out_map.at("specifier") += "/";
			}
		} */

		if (out_map.at("parameter").size()) {
			out_map.at("specifier") += ";";
			out_map.at("specifier") += out_map.at("parameter");
		}
		if (out_map.at("query").size()) {
			out_map.at("specifier") += "?";
			out_map.at("specifier") += out_map.at("query");

			/*
			vecbuf.assign(out_map.at("query").begin(), out_map.at("query").end());
			vecbuf.push_back('\0');
			if (uriUnescapeInPlaceA(vecbuf.data())) {
				out_map.at("query").assign(vecbuf.data());
			}
			vecbuf.clear();
			*/
		}
		if (out_map.at("fragment").size()) {
			out_map.at("specifier") += "#";
			out_map.at("specifier") += out_map.at("fragment");

			/*
			vecbuf.assign(out_map.at("fragment").begin(), out_map.at("fragment").end());
			vecbuf.push_back('\0');
			if (uriUnescapeInPlaceA(vecbuf.data())) {
				out_map.at("fragment").assign(vecbuf.data());
			}
			vecbuf.clear();
			*/
		}

		result = true;
	}
	uriFreeUriMembersA(&uri_parse);

	return result;
}

}}} /* EONS */

/* EOF */