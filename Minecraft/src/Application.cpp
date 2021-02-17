#include "pch.h"

#include "Application.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"

#define BIND_EVENT_FN(func) std::bind(&func, this, std::placeholders::_1)

Application* Application::s_Instance = nullptr;

Application::Application()
	:m_LastFrameTime(0.0f)
{	
	if (s_Instance)
	{
		spdlog::error("Application already exists!");
		return;
	}
	
	s_Instance = this;

	spdlog::trace("Creating window");
	m_Window = new Window();
	m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	spdlog::info(glGetString(GL_VERSION));

	float vertices[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	m_Vao = new VertexArray();

	m_Buffer = new VertexBuffer(vertices, 8 * sizeof(float));
	m_Buffer->Bind();

	m_Layout = new VertexBufferLayout({
			{GL_FLOAT, 2, GL_FALSE}
	});

	m_IndexBuffer = new IndexBuffer(indices, 6);

	m_Vao->AddBuffer(*m_Buffer, *m_Layout);

	m_BlueTriangle = new Shader("res/shaders/shader.glsl");
	m_BlueTriangle->Use();
}

void Application::OnUpdate(float timestep)
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
	glfwSwapBuffers(m_Window->GetRawWindow());
	glfwPollEvents();
}

void Application::OnEvent(Event& e)
{
	EventDispacher dispacher(e);
	dispacher.Dispach<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

	spdlog::trace(e.ToString());
}

void Application::Run()
{
	while (m_Running)
	{
		float time = (float)glfwGetTime();
		float ts = time - m_LastFrameTime;
		//spdlog::warn("Frame time {}", ts);
		OnUpdate(ts);
		glfwPollEvents();
		m_LastFrameTime = time;
	}
}

Application::~Application()
{
	delete m_Vao;
	delete m_Buffer;
	delete m_IndexBuffer;
	delete m_Layout;
	delete m_BlueTriangle;

	spdlog::trace("Application closed");
}

bool Application::OnWindowClose(WindowCloseEvent& event)
{
	spdlog::trace("Closing application");
	m_Running = false;
	return true;
}
