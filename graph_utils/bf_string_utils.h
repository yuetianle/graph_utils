/**
 * @file bf_string_utils.h
 * @brief  字符串相关操作
 *
 * @version 1.2.1
 * @author 李世达 lishida@hzzh.com
 * @date 2020/10/13
 * @copyright Copyright (c) 2020, 北京中恒博瑞数字电力有限公司 All rights reserved
 *
 */

#ifndef _bf_string_utils_h_
#define _bf_string_utils_h_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

#include "boost/format.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/locale.hpp"

//using std::string;


namespace BF_COMMON
{
	/**
	 * @brief bf_contain_substr_i 源字符串是否包含字串(不区分大小写)
	 * @param [in] src_str 源字符串
	 * @param [in] sub_str 子串
	 * @return bool
	 * - true 成功
	 * - false 失败
	 */
	inline bool bf_contain_substr_i(const std::string &src_str, const std::string &sub_str)
	{
		return boost::icontains(src_str, sub_str);
	}
	/**
	 * @brief bf_contain_substr 源字符串是否包含子串
	 * @param [in] src_str 源字符串
	 * @param [in] sub_str 子串
	 * @return bool
	 * - true 成功
	 * - false 失败
	 */
	inline bool bf_contain_substr(const std::string &src_str, const std::string &sub_str)
	{
		return boost::contains(src_str, sub_str);
	}
	/**
 * @brief bf_str_to_lower 转换字符串为小写
 * @param [in] src_str 源字符串
 * @return std::string 小写字符串
 */
inline std::string bf_str_to_lower(const std::string&src_str)
{
	std::string out_str;
	boost::to_lower_copy(back_inserter(out_str), src_str);
	return std::move(out_str);
}
/**
 * @brief bf_str_to_upper 转换字符串为大写
 * @param [in] src_str 源字符串
 * @return std::string 大写字符串
 */
inline std::string bf_str_to_upper(const std::string&src_str)
{
	std::string out_str;
	boost::to_upper_copy(back_inserter(out_str), src_str);
	return std::move(out_str);
}
	/**
	 * @brief 检查字符串是否相等
	 * @param [in] src 字符串
	 * @param [in] target 字符串
	 *
	 * @return 相等true 不相等false
	 */
	inline bool bf_str_compare(const std::string& src, const std::string &target)
	{
		return boost::equals(src, target);
	}

	/**
	 * @brief 检查字符串是否相等(不区分大小写)
	 *
	 * @param [in] src 字符串
	 * @param [in] target 字符串
	 *
	 * @return 相等true 不相等false
	 */
	inline bool bf_str_compare_i(const std::string& src, const std::string &target)
	{
		return boost::iequals(src, target);
	}

	/**
	 * @brief 基本数据类型转为String
	 *
	 * @param [in] src 待转换对象
	 *
	 * @return 返回转换的字符串
	 * float 10.23 return "10.23"
	 */
	template<typename T>
	inline std::string bf_to_string(const T &src)
	{
		return std::move(boost::lexical_cast<std::string>(src));
	}

	/**
	 * @brief float设置固定位数
	 *
	 * @param [in] data 原数据
	 * @param [in] width 小数宽度
	 *
	 * @return 转换后的数据
	 */
	inline float bf_float_width(const float &data, const int &width = 4)
	{
		std::stringstream ss;
		ss.precision(width);
		ss << std::setw(width) << data;
		return std::move(boost::lexical_cast<float>(ss.str()));
	}

	/*
	 * @brief 拆分字符串到Vector
	 * @param [out] out_vec_str 输出字符数组
	 * @param [in] src 源字符串
	 * @param [in] sep 分割字符串
	 * @return 分割后的字符Vector的个数
	 */
	inline size_t bf_string_split(std::vector<std::string>& out_vec_str, const std::string &src, const std::string &sep = ",")
	{
		if (src.empty())
		{
			return 0;
		}

		std::string tmp;
		std::string::size_type pos_begin = src.find_first_not_of(sep);
		std::string::size_type comma_pos = 0;

		while (pos_begin != std::string::npos)
		{
			comma_pos = src.find(sep, pos_begin);
			if (comma_pos != std::string::npos)
			{
				tmp = src.substr(pos_begin, comma_pos - pos_begin);
				pos_begin = comma_pos + sep.length();
			}
			else
			{
				tmp = src.substr(pos_begin);
				pos_begin = comma_pos;
			}

			if (!tmp.empty())
			{
				out_vec_str.push_back(tmp);
				tmp.clear();
			}
		}
		return out_vec_str.size();

	}
	inline std::string format_helper(boost::format& f)
	{
		return f.str();
	}

	template<typename T, typename ...Args>
	inline std::string format_helper(boost::format& f, T&& value, Args&&... args)
	{
		return format_helper(f%std::forward<T>(value), std::forward<Args>(args)...);
	}

	/*
	 * @brief bf_format 格式化字符串
	 * @access public
	 * @param [in] fmt 格式串
	 * @param [in] args 可变参数
	 * @return std::string 格式化后字符串
	 */
	template<typename... Args>
	inline std::string bf_format(const std::string &fmt, Args&&... args)
	{
		boost::format f(fmt);
		format_helper(f, std::forward<Args>(args)...);
		return move(f.str());
	}

	/*
	 * @brief bf_to_utf8 转换字符串编码到UTF-8
	 * @access public
	 * @param [in] str 输入字符串
	 * @param [in] loc 输入字符串编码
	 * @return string 返回编码后字符串
	 */
	inline std::string bf_to_utf8(const std::string &str, const std::string loc = "GBK")
	{
		std::string const &to_encoding("UTF-8");
		std::string const &from_encoding(loc);
		std::string result = boost::locale::conv::between(str.c_str(), str.c_str() + str.size(), to_encoding, from_encoding, boost::locale::conv::default_method);
		return result;
	}
    /**
     *
     *
     *
     */
    inline std::string bf_to_gbk(const std::string &str, const std::string loc = "GBK")
    {
		std::string const &to_encoding(loc);
		std::string const &from_encoding("UTF-8");
		std::string result = boost::locale::conv::between(str.c_str(), str.c_str() + str.size(), to_encoding, from_encoding, boost::locale::conv::default_method);
		return result;

    }
	inline bool bf_is_utf8(const char* str)
	{
		unsigned int nBytes = 0;
		unsigned char chr = *str;
		bool bAllAscii = true;
		for (unsigned int i = 0; str[i] != '\0'; ++i) {
			chr = *(str + i);
			if (nBytes == 0 && (chr & 0x80) != 0) {
				bAllAscii = false;
			}
			if (nBytes == 0) {
				if (chr >= 0x80) {
					if (chr >= 0xFC && chr <= 0xFD) {
						nBytes = 6;
					}
					else if (chr >= 0xF8) {
						nBytes = 5;
					}
					else if (chr >= 0xF0) {
						nBytes = 4;
					}
					else if (chr >= 0xE0) {
						nBytes = 3;
					}
					else if (chr >= 0xC0) {
						nBytes = 2;
					}
					else {
						return false;
					}
					nBytes--;
				}
			}
			else {
				if ((chr & 0xC0) != 0x80) {
					return false;
				}
				nBytes--;
			}
		}
		if (nBytes != 0) {
			return false;
		}
		if (bAllAscii) {
			return true;
		}
		return true;
	}
	/**
	 * @brief bf_ends_with 检查字符串是否已某个后缀结尾
	 * @param [in] src_str 源字符串
	 * @param [in] suffix 后缀
	 * @return bool
	 * - true 成功
	 * - false 失败
	 */
	inline bool bf_ends_with(const std::string &src_str, const std::string &suffix)
	{
		if (src_str.empty() || suffix.empty())
			return false;
		return boost::ends_with(src_str, suffix);
	}
	/**
	 * @brief bf_iends_with 检查字符串是否已某个后缀结尾(不区分大小写)
	 * @param [in] src_str 源字符串
	 * @param [in] suffix 后缀
	 * @return bool
	 * - true 成功
	 * - false 失败
	 */
	inline bool bf_iends_with(const std::string &src_str, const std::string &suffix)
	{
		if (src_str.empty() || suffix.empty())
			return false;
		return boost::iends_with(src_str, suffix);
	}
}
#endif
