//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <lang/Generated/Types.h>
#include <lang/Script.h>

#include <obj/Indexer.h>
#include <lang/Lua.h>

namespace mud
{
	Script::Script(cstring name, const Signature& signature)
		: Callable(name, signature.m_params, signature.m_returnval)
		, m_index(index(type<Script>(), this))
		, m_name(name)
		, m_signature(signature)
	{}

	Script::~Script()
	{
		unindex(type<Script>(), m_index);
	}

	void Script::operator()(array<Var> args, Var& result) const
	{
		for(const Param& param : m_signature.m_params)
			m_interpreter->set(param.m_name, args[param.m_index]);

		m_interpreter->call(m_script.c_str(), &result);
	}
}
