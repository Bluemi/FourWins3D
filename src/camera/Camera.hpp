#ifndef __CAMERA_CLASS__
#define __CAMERA_CLASS__

#include <glm/glm.hpp>

#include <interaction/MouseListener.hpp>

class Camera : public MouseListener
{
	public:
		Camera(const glm::vec3 &position, const float pitch, const float yaw);
		glm::vec3 getUp() const;
		glm::vec3 getRight() const;
		glm::vec3 getDirection() const;
		glm::vec3 getTop() const;
		glm::mat4 getLookAt() const;

		void captureMouse();
		virtual void onMouseMoved(glm::vec2 diff) override;

		void goForward();
		void goBackward();
		void goLeft();
		void goRight();
		void goTop();
		void goBottom();
	private:
		const float camSpeed = 0.05f;
		glm::vec3 position;

		float pitch;
		float yaw;

		const float CAMERA_ROTATE_SPEED = 0.05f;
};

#endif
