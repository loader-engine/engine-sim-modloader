#pragma once

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <map>

namespace djson {

	enum jsonVarType {
		string,
		integer,
		floating,
		precision
	};

	struct jsonVar {
		jsonVarType type = string;

		void fromString(std::string str) {
			_string = str;
		}

		void fromInt(int i) {
			type = integer;
			_integer = i;
		}

		void fromFloat(float f) {
			type = floating;
			_floating = f;
		}

		void fromDouble(double d) {
			type = precision;
			_precision = d;
		}

		std::string toString() {
			if (type == string)    return "\"" + _string + "\"";
			if (type == integer)   return std::to_string(_integer);
			if (type == floating)  return std::to_string(_floating);
			if (type == precision) return std::to_string(_floating);

			return "";
		}

	private:
		std::string _string = "";
		int _integer = 0;
		float _floating = 0.0f;
		double _precision = 0.0;
	};

	struct json {
		std::map<std::string, djson::jsonVar> items;
		int len = 0;

		void addString(std::string key, std::string var) {
			djson::jsonVar jVar;
			jVar.fromString(var);

			add(key, jVar);
		}

		void addInt(std::string key, int var) {
			djson::jsonVar jVar;
			jVar.fromInt(var);

			add(key, jVar);
		}

		void addFloat(std::string key, float var) {
			djson::jsonVar jVar;
			jVar.fromFloat(var);

			add(key, jVar);
		}

		void addDouble(std::string key, double var) {
			djson::jsonVar jVar;
			jVar.fromDouble(var);

			add(key, jVar);
		}

		std::string toString() {
			std::string out;
			int indent = 1;

			out += "{\n";

			int count = 1;
			for (std::pair<std::string, djson::jsonVar> var : items)
			{
				for (int i = 0; i < indent; i++) {
					out += "    ";
				}

				out += "\"" + var.first + "\": " + var.second.toString();
				
				if (count != len) {
					out += ",";
				}

				out += "\n";

				count++;
			}

			out += "}\n";

			return out;
		}

	private:
		void add(std::string key, djson::jsonVar var) {
			items.insert(std::pair<std::string, djson::jsonVar>(key, var));
			len++;
		}
	};

}
