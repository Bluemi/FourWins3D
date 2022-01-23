#ifndef __CAMERA_CLASS__
#define __CAMERA_CLASS__

#include <glm/glm.hpp>

#include <interaction/MouseListener.hpp>
#include <interaction/KeyboardListener.hpp>

class Camera : public MouseListener, public KeyboardListener
{
	public:
		Camera(const glm::vec3 &position, const float pitch, const float yaw);

		void tick();
		void stop();

		glm::vec3 getUp() const;
		glm::vec3 getRight() const;
		glm::vec3 getDirection() const;
		glm::vec3 getTop() const;
		glm::mat4 getLookAt() const;

		glm::vec3 getPosition() const;

		void captureMouse();
		void captureKeyboard();

		virtual void onMouseMoved(glm::vec2 diff) override;
		virtual void onKeyPressed(const int key) override;
		virtual void onKeyReleased(const int key) override;

		void printStats() const;
	private:
		const float CAMERA_SPEED = 0.03f;
		const float CAMERA_ROTATE_SPEED = 0.1f;
		const float CAMERA_DRAG = 0.78f;

		glm::vec3 position;
		glm::vec3 speed;

		float pitch;
		float yaw;

		char moveForward;
		char moveRight;
		char moveTop;
};

#endif
