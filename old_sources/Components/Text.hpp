#ifndef INDIE_STUDIO_TEXT_HPP
#define INDIE_STUDIO_TEXT_HPP

#include "ECS/Component.hpp"

namespace ECS {
    namespace Components {
		class Text : public ECS::Component {
		public:
			Text(const std::string& text) : text(text) {
			}

			~Text() override = default;

            const std::string &text;
        };
    }
}

#endif