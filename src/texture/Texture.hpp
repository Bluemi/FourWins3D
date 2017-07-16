#ifndef __TEXTURE_CLASS__
#define __TEXTURE_CLASS__

#include <string>

class Texture
{
	public:
		Texture();
		~Texture();
		void load(const std::string &path) const;
		void use() const;
	private:
		unsigned int id;
};

#endif
