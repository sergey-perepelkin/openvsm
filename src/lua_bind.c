/**
 *
 * @file   lua_bind.c
 * @Author Lavrentiy Ivanov (ookami@mail.ru)
 * @date   22.09.2014
 * @brief  Brief description of file.
 *
 * This file is part of OpenVSM.
 * OpenVSM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenVSM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenVSM.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <vsm_api.h>

static const lua_bind_var lua_var_api_list[]=
{
	{.var_name="SHI", .var_value=SHI},
	{.var_name="SLO", .var_value=SLO},
	{.var_name="FLT", .var_value=FLT},
	{.var_name="PLO", .var_value=PLO},
	{.var_name="ILO", .var_value=ILO},
	{.var_name="WLO", .var_value=WLO},
	{.var_name="WHI", .var_value=WHI},
	{.var_name="IHI", .var_value=IHI},
	{.var_name="PHI", .var_value=PHI},
	{.var_name="WUD", .var_value=WUD},
	{.var_name="SUD", .var_value=SUD},
	{.var_name="TSTATE", .var_value=TSTATE},
	{.var_name="FSTATE", .var_value=FSTATE},
	{.var_name="UNDEFINED", .var_value=UNDEFINED},
	{.var_name="MSEC", .var_value=1000000000L},
	{.var_name="NSEC", .var_value=100000000L},
	{.var_name="SEC", .var_value=1000000000000L},
	{.var_name="NOW", .var_value=0L},
	{.var_name=NULL},
};

static const lua_bind_func lua_c_api_list[] =
{
	{.lua_func_name="state_to_string", .lua_c_api=&lua_state_to_string, .args={LSTRING}},
	{.lua_func_name="is_pin_active", .lua_c_api=&lua_is_pin_active, .args={LINT}},
	{.lua_func_name="is_pin_edge", .lua_c_api=&lua_is_pin_edge, .args={LINT}},
	{.lua_func_name="is_pin_posedge", .lua_c_api=&lua_is_pin_posedge, .args={LINT}},
	{.lua_func_name="is_pin_negedge", .lua_c_api=&lua_is_pin_negedge, .args={LINT}},
	{.lua_func_name="set_pin_state", .lua_c_api=&lua_set_pin_state, .args={LINT}},
	{.lua_func_name="set_pin_bool", .lua_c_api=&lua_set_pin_bool, .args={LINT,LINT}},
	{.lua_func_name="get_pin_bool", .lua_c_api=&lua_get_pin_bool, .args={LINT}},
	{.lua_func_name="get_pin_state", .lua_c_api=&lua_get_pin_state, .args={LINT}},
	{.lua_func_name="is_pin_low", .lua_c_api=&lua_is_pin_low, .args={LINT}},
	{.lua_func_name="is_pin_high", .lua_c_api=&lua_is_pin_high, .args={LINT}},
	{.lua_func_name="is_pin_floating", .lua_c_api=&lua_is_pin_floating, .args={LINT}},
	{.lua_func_name="toggle_pin", .lua_c_api=&lua_toggle_pin_state, .args={LINT}},
	{.lua_func_name="info", .lua_c_api=&lua_print_info, .args={LSTRING}},
	{.lua_func_name="message", .lua_c_api=&lua_print_message, .args={LSTRING}},
	{.lua_func_name="warning", .lua_c_api=&lua_print_warning, .args={LSTRING}},
	{.lua_func_name="error", .lua_c_api=&lua_print_error, .args={LSTRING}},
	{.lua_func_name="set_callback", .lua_c_api=&lua_set_callback, .args={LINT, LINT}},
	{.lua_func_name="create_debug_popup", .lua_c_api=&lua_create_debug_popup, .args={LSTRING}},
	{.lua_func_name="create_memory_popup", .lua_c_api=&lua_create_memory_popup, .args={LSTRING}},
	{.lua_func_name="create_source_popup", .lua_c_api=&lua_create_source_popup, .args={LSTRING}},
	{.lua_func_name="create_status_popup", .lua_c_api=&lua_create_status_popup, .args={LSTRING}},
	{.lua_func_name="create_var_popup", .lua_c_api=&lua_create_var_popup, .args={LSTRING}},
	{.lua_func_name="delete_popup", .lua_c_api=&lua_delete_popup, .args={LINT}},
	{.lua_func_name="set_memory_popup", .lua_c_api=&lua_set_memory_popup, .args={}},
	{.lua_func_name="repaint_memory_popup", .lua_c_api=&lua_repaint_memory_popup, .args={}},
	{.lua_func_name="print_to_debug_popup", .lua_c_api=&lua_print_to_debug_popup, .args={}},
	{.lua_func_name="dump_to_debug_popup", .lua_c_api=&lua_dump_to_debug_popup, .args={}},
	{.lua_func_name="get_string_param", .lua_c_api=&lua_get_string_param, .args={}},
	{.lua_func_name="get_num_param", .lua_c_api=&lua_get_num_param, .args={}},
	{.lua_func_name="get_bool_param", .lua_c_api=&lua_get_bool_param, .args={}},
	{.lua_func_name="get_init_param", .lua_c_api=&lua_get_init_param, .args={}},
	{.lua_func_name="get_hex_param", .lua_c_api=&lua_get_hex_param, .args={}},
	{.lua_func_name="add_source_file", .lua_c_api=&lua_add_source_file, .args={}},
	{.lua_func_name="get_bit", .lua_c_api=&lua_get_bit, .args={LINT, LINT}},
	{.lua_func_name="set_bit", .lua_c_api=&lua_set_bit, .args={LINT, LINT}},
	{.lua_func_name="clear_bit", .lua_c_api=&lua_clear_bit, .args={LINT, LINT}},
	{.lua_func_name="toggle_bit", .lua_c_api=&lua_toggle_bit, .args={LINT, LINT}},
	{.lua_func_name="systime", .lua_c_api=&lua_get_systime },
	{.lua_func_name="set_bus", .lua_c_api=&lua_set_bus,  .args={}},
	{.lua_func_name="get_bus", .lua_c_api=&lua_get_bus,  .args={} },
	{ NULL, NULL},
};

static void
SAFE_EXECUTE ( lua_State* L, void* curfunc )
{
#ifdef __DEBUG
	int argnum = lua_gettop ( L );
	for ( int i=0; lua_c_api_list[i].lua_func_name; i++ )
	{
		if ( curfunc == lua_c_api_list[i].lua_c_api )
		{
			int argcount=0;
			for ( argcount=0; lua_c_api_list[i].args[argcount]; argcount++ )
			{
				if ( argnum < argcount+1 )
				{
					IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
					lua_Debug ar;
					lua_getstack(L, 1, &ar);
					lua_getinfo(L, "nSl", &ar);
					int line = ar.currentline;				
					
					print_error ( model, "Line %d: Too few arguments passed to the function \"%s\"", line, lua_c_api_list[i].lua_func_name );
				}
				else if ( !lua_c_api_list[i].args[argcount] ( L, argcount+1 ) )
				{
					IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
					lua_Debug ar;
					lua_getstack(L, 1, &ar);
					lua_getinfo(L, "nSl", &ar);
					int line = ar.currentline;				
					print_error ( model, "Line %d: Argument %d of \"%s\" is of wrong type [%s]", line, argcount+1, lua_c_api_list[i].lua_func_name, lua_typename (L, argcount+1) );
				}  
			}		
			if(lua_c_api_list[i].args[argcount+1])	
			{
				IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
				lua_Debug ar;
				lua_getstack(L, 1, &ar);
				lua_getinfo(L, "nSl", &ar);
				int line = ar.currentline;				
				print_error ( model, "Line %d: extra arguments passed to \"%s\"", line, argcount+1, lua_c_api_list[i].lua_func_name );
			}
		}
	}
#endif
}

void
register_functions ( IDSIMMODEL* model, lua_State* L )
{
	/*  Declare functions */
	for ( int i=0; lua_c_api_list[i].lua_func_name; i++ )
	{
		lua_pushcfunction ( L, lua_c_api_list[i].lua_c_api );
		lua_setglobal ( L, lua_c_api_list[i].lua_func_name );
	}
	/* Declare variables */
	for ( int i=0; lua_var_api_list[i].var_name ; i++ )
	{
		lua_pushnumber ( L, lua_var_api_list[i].var_value );
		lua_setglobal ( L, lua_var_api_list[i].var_name );
	}
}

bool
load_device_script ( IDSIMMODEL* model, const char* device_name )
{
	char spath[512] = {0};
	if ( 0 == GetEnvironmentVariable ( "LUAVSM", spath, sizeof spath ) )
	{
		print_error ( model, "LUAVSM environment variable is not set" );
		return false;
	}
	char* script=NULL;
	asprintf ( &script, "%s%s%s", spath, '\\' == spath[strlen ( spath )-1]? "":"\\", device_name );

	int lua_err = luaL_loadfile ( model->luactx, script );

	if ( 0 != lua_err )
	{
		free ( script );
		const char* mess = NULL;
		switch ( lua_err )
		{
			case LUA_ERRSYNTAX:
				mess = lua_tostring ( model->luactx, -1 );
				print_error ( model, "Syntax error in Lua script\n%s", mess );
				return false;
			case LUA_ERRMEM:
				print_error ( model, "Not enough memory to load script" );
				return false;
			case LUA_ERRFILE:
				print_error ( model, "Error loading script file" );
				return false;
			default:
				print_error ( model, "Unknown error, shouldn't happen" );
				assert ( 0 );
		}
	}
	/* Primer run, if not run it - nothing works, need for parse */
	if ( 0 != lua_pcall ( model->luactx, 0, 0, 0 ) )
	{
		print_error ( model, "Failed to load the script \"%s\"", script );
		free ( script );
		return false;
	}
	free ( script );
	return true;
}

static int
lua_get_string_param ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_get_string_param );
	char* str = ( char* ) lua_tostring ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushstring ( L, get_string_param ( model, str ) );
	return 1;
}

static int
lua_get_bool_param ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_get_bool_param );
	char* str = ( char* ) lua_tostring ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushboolean ( L, get_bool_param ( model, str ) );
	return 1;
}

static int
lua_get_num_param ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_get_num_param );
	char* str = ( char* ) lua_tostring ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushnumber ( L, get_num_param ( model, str )  );
	return 1;
}

static int
lua_get_hex_param ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_get_hex_param );
	char* str = ( char* ) lua_tostring ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushnumber ( L, get_hex_param ( model,str ) );
	return 1;
}

static int
lua_get_init_param ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_get_init_param );
	char* str = ( char* ) lua_tostring ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushnumber ( L, get_init_param ( model, str ) );
	return 1;
}

static int
lua_delete_popup ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_delete_popup );
	int id = lua_tointeger ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	delete_popup ( model, id );
	return 0;
}

static int
lua_create_debug_popup ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_create_debug_popup );
	const char* text = lua_tostring ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushlightuserdata ( L, create_debug_popup ( model, text, ++popup_id ) );
	lua_pushnumber ( L, popup_id );
	return 2;
}

/**
* Prints a text string to debug popup
* @param L Lua state
* @return a pointer to popup and its ID
*/
static int
lua_print_to_debug_popup ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_print_to_debug_popup );
	const char* str = lua_tostring ( L, -1 );
	void* popup = lua_touserdata ( L, -2 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	print_to_debug_popup ( popup,  str );
	return 0;
}

/**
* Prints a text string to debug popup
* @param L Lua state
* @return a pointer to popup and its ID
*/
static int
lua_dump_to_debug_popup ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_dump_to_debug_popup );
	lua_Number offset = luaL_checknumber ( L,-1 );
	lua_Number size = luaL_checknumber ( L,-2 );
	const char* buf = luaL_checkstring ( L,-3 );
	void* popup = lua_touserdata ( L, -4 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	dump_to_debug_popup ( popup, ( BYTE* ) buf, offset, size );
	return 0;
}

static int
lua_create_source_popup ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_create_source_popup );
	const char* text = lua_tostring ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushlightuserdata ( L, create_source_popup ( model, text, ++popup_id ) );
	lua_pushnumber ( L, popup_id );
	return 2;
}
static int
lua_create_status_popup ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_create_status_popup );
	const char* text = lua_tostring ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushlightuserdata ( L, create_status_popup ( model, text, ++popup_id ) );
	lua_pushnumber ( L, popup_id );
	return 2;
}
static int
lua_create_var_popup ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_create_var_popup );
	const char* text = lua_tostring ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushlightuserdata ( L, create_var_popup ( model, text, ++popup_id ) );
	lua_pushnumber ( L, popup_id );
	return 2;
}

static int
lua_create_memory_popup ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_create_memory_popup );
	const char* text = lua_tostring ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushlightuserdata ( L, create_memory_popup ( model, text, ++popup_id ) );
	lua_pushnumber ( L, popup_id );
	return 2;
}

static int
lua_set_memory_popup ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_set_memory_popup );
	lua_Number size = luaL_checknumber ( L,-1 );
	const char* buf = luaL_checkstring ( L,-2 );
	void* popup = lua_touserdata ( L, -3 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	set_memory_popup ( popup, 0, ( void* ) buf, size );

	return 0;
}

static int
lua_add_source_file ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_add_source_file );
	if ( false == add_source_file ( lua_touserdata ( L, -3 ), ( char* ) lua_tostring ( L, -2 ), lua_tointeger ( L, -1 ) ) )
	{
		IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
		print_info ( model, "Fail to load source file" );
	}

	return 0;
}

static int
lua_repaint_memory_popup ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_repaint_memory_popup );
	void* popup = lua_touserdata ( L, -1 ) ;
	repaint_memory_popup ( popup );
	return 0;
}

static int
lua_set_pin_state ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_set_pin_state );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	int pin_num = lua_tointeger ( L, -2 );
	int pin_state = lua_tointeger ( L, -1 );	
	set_pin_state ( model, model->device_pins[pin_num], pin_state );
	return 0;
}

static int
lua_get_pin_state ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_get_pin_state );
	int pin_num = lua_tointeger ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );

	if ( TRUE == is_pin_high ( model->device_pins[pin_num].pin ) )
	{
		lua_pushnumber ( L, SHI );
		return 1;
	}
	else if ( TRUE == is_pin_low ( model->device_pins[pin_num].pin ) )
	{
		lua_pushnumber ( L, SLO );
		return 1;
	}
	else if ( TRUE == is_pin_floating ( model->device_pins[pin_num].pin ) )
	{
		lua_pushnumber ( L, FLT );
		return 1;
	}
	else
	{
		lua_pushnumber ( L, UNDEFINED );
		return 1;
	}
}

static int
lua_set_pin_bool ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_set_pin_bool );
	int pin_num = lua_tointeger ( L, -2 );
	int pin_level = lua_tointeger ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	set_pin_bool ( model, model->device_pins[pin_num], pin_level );
	return 0;
}

static int
lua_get_pin_bool ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_get_pin_bool );
	int pin_num = lua_tointeger ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	if ( TRUE == is_pin_high ( model->device_pins[pin_num].pin ) )
	{
		lua_pushboolean ( L,  1 );
		return 1;
	}
	else if ( TRUE == is_pin_low ( model->device_pins[pin_num].pin ) )
	{
		lua_pushboolean ( L,  0 );
		return 1;
	}
	lua_pushnil ( L );
	return 1;
}

static int
lua_state_to_string ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_state_to_string );
	int state = lua_tointeger ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );

	lua_pushstring ( L,  state_to_string ( state ) );
	return 1;
}

static int
lua_is_pin_low ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_is_pin_low );
	int pin_num = lua_tointeger ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushboolean ( L, is_pin_low ( model->device_pins[pin_num].pin ) );
	return 1;
}

static int
lua_is_pin_high ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_is_pin_high );
	int pin_num = lua_tointeger ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushboolean ( L, is_pin_high ( model->device_pins[pin_num].pin ) );
	return 1;
}

static int
lua_is_pin_edge ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_is_pin_edge );
	int pin_num = lua_tointeger ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushboolean ( L, is_pin_edge ( model->device_pins[pin_num].pin ) );
	return 1;
}

static int
lua_is_pin_posedge ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_is_pin_posedge );
	int pin_num = lua_tointeger ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushboolean ( L, is_pin_posedge ( model->device_pins[pin_num].pin ) );
	return 1;
}

static int
lua_is_pin_negedge ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_is_pin_negedge );
	int pin_num = lua_tointeger ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushboolean ( L, is_pin_negedge ( model->device_pins[pin_num].pin ) );
	return 1;
}

static int
lua_is_pin_active ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_is_pin_active );
	int pin_num = lua_tointeger ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushboolean ( L, is_pin_active ( model->device_pins[pin_num].pin ) );
	return 1;
}

static int
lua_toggle_pin_state ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_toggle_pin_state );
	int pin_num = lua_tointeger ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	toggle_pin_state ( model, model->device_pins[pin_num] );
	return 0;
}

static int
lua_is_pin_floating ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_is_pin_floating );
	int pin_num = lua_tointeger ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	lua_pushboolean ( L, is_pin_floating ( model->device_pins[pin_num].pin ) );
	return 1;
}

static int
lua_print_info ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_print_info );
	const char* text = lua_tostring ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	print_info ( model, text );
	return 0;
}

static int
lua_print_message ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_print_message );
	const char* text = lua_tostring ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	print_message ( model, text );
	return 0;
}

static int
lua_print_warning ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_print_warning );
	const char* text = lua_tostring ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	print_warning ( model, text );
	return 0;
}

static int
lua_print_error ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_print_error );
	const char* text = lua_tostring ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	print_error ( model, text );
	return 0;
}

static int
lua_set_callback ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_set_callback );
	lua_Number picotime = lua_tointeger ( L, -2 );
	lua_Number eventid = lua_tointeger ( L, -1 );
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	set_callback ( model, picotime, eventid );
	return 0;
}

static int
lua_get_systime ( lua_State* L )
{
	ABSTIME curtime = 0;
	IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	systime ( model, &curtime );
	lua_pushnumber ( L, curtime );
	return 1;
}

static int
lua_get_bit ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_get_bit );
	size_t byte = lua_tointeger ( L, -2 );
	size_t bit = lua_tointeger ( L, -1 );
	lua_pushnumber ( L, ( byte >> bit & 0x01 ) );
	return 1;
}

static int
lua_clear_bit ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_clear_bit );
	size_t byte = lua_tointeger ( L, -2 );
	size_t bit = lua_tointeger ( L, -1 );
	byte &= ~ ( 1 << bit );
	lua_pushnumber ( L, byte );
	return 1;
}

static int
lua_set_bit ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_set_bit );
	size_t byte = lua_tointeger ( L, -2 );
	size_t bit = lua_tointeger ( L, -1 );
	byte |= ( 1 << bit );
	lua_pushnumber ( L, byte );
	return 1;
}

static int
lua_toggle_bit ( lua_State* L )
{
	SAFE_EXECUTE ( L, &lua_toggle_bit );
	size_t byte = lua_tointeger ( L, -2 );
	size_t bit = lua_tointeger ( L, -1 );
	byte ^= 1 << bit;
	lua_pushnumber ( L, byte );
	return 1;
}

static void* lua_get_model_obj ( lua_State* L )
{
	lua_pushliteral ( L, "__this" );
	lua_gettable ( L, LUA_REGISTRYINDEX );
	void *this = lua_touserdata ( L, -1 );
	lua_pop(L, 1);
	return this;
}

static int lua_set_bus ( lua_State* L )
{		
	if (0 == lua_istable(L, 1))
	{
		IDSIMMODEL* model = ( IDSIMMODEL* ) lua_get_model_obj ( L );
	    print_info(model, "No bus specified");
	}
	/*lua_pushnil(luactx);
	while (lua_next(luactx, 1) != 0) 
	{    
	print_info(lua_typename(luactx, lua_type(luactx, -1)));   
	lua_pop(luactx, 1);
	}*/
	return 0;
}

static int lua_get_bus ( lua_State* L )
{	
	return 0;
}