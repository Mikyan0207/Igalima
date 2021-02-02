#pragma once

#include <string>
#include <OBJ_Loader.h>

class Model
{
	public:
		Model(const std::string& path);
		Model(const Model&) = default;
		Model(Model&&) noexcept = default;
		~Model() = default;

 	public:
		Model& operator=(const Model&) = default;
		Model& operator=(Model&&) noexcept = default;

};