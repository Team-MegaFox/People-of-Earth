#include "GUIEngine.h"

OpenGL3Renderer * GUIEngine::m_renderer = nullptr;

GUIEngine::GUIEngine(const std::string & resourceDir)
{
	// Check if the renderer and system were not already initialized
	if (m_renderer == nullptr) {
		m_renderer = &OpenGL3Renderer::bootstrapSystem();

		DefaultResourceProvider* rp = static_cast<DefaultResourceProvider*>(System::getSingleton().getResourceProvider());
		rp->setResourceGroupDirectory("imagesets", resourceDir + "/imagesets/");
		rp->setResourceGroupDirectory("schemes", resourceDir + "/schemes/");
		rp->setResourceGroupDirectory("fonts", resourceDir + "/fonts/");
		rp->setResourceGroupDirectory("layouts", resourceDir + "/layouts/");
		rp->setResourceGroupDirectory("looknfeels", resourceDir + "/looknfeel/");
		rp->setResourceGroupDirectory("lua_scripts", resourceDir + "/lua_scripts/");

		ImageManager::setImagesetDefaultResourceGroup("imagesets");
		Scheme::setDefaultResourceGroup("schemes");
		Font::setDefaultResourceGroup("fonts");
		WidgetLookManager::setDefaultResourceGroup("looknfeels");
		WindowManager::setDefaultResourceGroup("layouts");
		ScriptModule::setDefaultResourceGroup("lua_scripts");
	}

	m_context = &System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
	m_root = WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	m_context->setRootWindow(m_root);
}

GUIEngine::~GUIEngine()
{
	System::getSingleton().destroyGUIContext(*m_context);
}


void GUIEngine::update(const float & deltaTime, const GameObject & gameObject)
{
	m_context->injectTimePulse(deltaTime);
}

void GUIEngine::render()
{
	// TODO : Do we need to glDisable(ScissorTest) here?

	m_renderer->beginRendering();
	m_context->draw();
	m_renderer->endRendering();
	glDisable(GL_SCISSOR_TEST);
}

void GUIEngine::processInput(SDL_Event & e)
{

}

void GUIEngine::setFont(const std::string & fontFile)
{
	FontManager::getSingleton().createFromFile(fontFile + ".font");
	m_context->setDefaultFont(fontFile);
}

void GUIEngine::setToRoot(GUIComponent & component)
{
	m_root->addChild(component.getWidget());
}

void GUIEngine::loadScheme(const std::string & scheme)
{
	SchemeManager::getSingleton().createFromFile(scheme);
}
