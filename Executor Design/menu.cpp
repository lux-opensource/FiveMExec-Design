#include "menu.h"
#include "settings.h"
#include "functions.h"
#include "imguipp.h"
#include "icons.h"
#include "TextEditor.h"

extern ImFont* Consolas;
void Menu::Render()
{
	ImGui::Columns(2);
	ImGui::SetColumnOffset(1, 230);

	{
		//Left side

		static ImVec4 active = imguipp::to_vec4(41, 40, 41, 255);
		static ImVec4 inactive = imguipp::to_vec4(31, 30, 31, 255);

		ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 1 ? active : inactive);
		if (ImGui::Button(ICON_FA_CODE " Lua Executor", ImVec2(230 - 15, 41)))
			Settings::Tab = 1;

		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 2 ? active : inactive);
		if (ImGui::Button(ICON_FA_DOWNLOAD " File Dumper", ImVec2(230 - 15, 41)))
			Settings::Tab = 2;

		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 3 ? active : inactive);
		if (ImGui::Button(ICON_FA_BUG " Resource Blocker", ImVec2(230 - 15, 41)))
			Settings::Tab = 3;

		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 4 ? active : inactive);
		if (ImGui::Button(ICON_FA_BOOK " Preloaded Menus", ImVec2(230 - 15, 41)))
			Settings::Tab = 4;

		ImGui::PopStyleColor(4);

		ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
		imguipp::center_text_ex("Lux", 230, 1, false);
	}

	ImGui::NextColumn();

	//Right side
	{
		
		// Executor tab
		if (Settings::Tab == 1)
		{
			static TextEditor editor;

			editor.SetShowWhitespaces(false);
			editor.SetReadOnly(false);
			editor.SetPalette(TextEditor::GetDarkPalette());
			editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());

			if (ImGui::Button(ICON_FA_FILE" Execute from file", ImVec2(200, 35))) {}

			ImGui::Spacing();
			ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 0);
			ImGui::PushFont(Consolas);
			editor.Render("##EditorWindow", ImVec2(imguipp::getx(), 300));
			ImGui::PopFont();
			ImGui::PopStyleVar();
			ImGui::Spacing();
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(7, 7));
			if (ImGui::BeginCombo("##CheatList", "_cfx_internal"))
			{
				ImGui::EndCombo();
			}
			ImGui::PopStyleVar();
			ImGui::SameLine();
			if (ImGui::Button(ICON_FA_CHECK" Execute", ImVec2(115, 34))) {}
			ImGui::SameLine();
			if (ImGui::Button(ICON_FA_SQUARE" Stop", ImVec2(imguipp::getx(), 34))) {}
		}

		// Dumper Tab
		else if (Settings::Tab == 2)
		{
			static ImGuiTextFilter filter;
			static std::vector<std::string> resources = 
			{
				"_cfx_internal",
				"mysql-async",
				"essentialmode",
				"async",
				"es_extended"
			};

			filter.Draw(ICON_FA_SEARCH" Search", 240);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 0));
			if (ImGui::ListBoxHeader("##ResourcesList", ImVec2(imguipp::getx(), imguipp::gety() - 35)))
			{
				for (const auto& resource : resources)
				{
					if (filter.PassFilter(resource.c_str()))
					{
						if (ImGui::TreeNode(resource.c_str()))
							ImGui::TreePop();				
					}
				}
				ImGui::ListBoxFooter();
			}
			ImGui::PopStyleColor();
			if (ImGui::Button(ICON_FA_FOLDER_OPEN" Save to folder", ImVec2(205, 34))) {}
		}		
	}
}

void Menu::Theme()
{
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowBorderSize = 0;
	style->WindowTitleAlign = ImVec2(0.5, 0.5);
	style->WindowMinSize = ImVec2(900, 430);

	style->FramePadding = ImVec2(8, 6);

	style->Colors[ImGuiCol_TitleBg] = ImColor(50, 78, 168, 255);
	style->Colors[ImGuiCol_TitleBgActive] = ImColor(50, 78, 168, 255);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 130);

	style->Colors[ImGuiCol_Button] = ImColor(31, 30, 31, 255);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(41, 40, 41, 255);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(41, 40, 41, 255);

	style->Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
	style->Colors[ImGuiCol_SeparatorActive] = ImColor(76, 76, 76, 255);
	style->Colors[ImGuiCol_SeparatorHovered] = ImColor(76, 76, 76, 255);

	style->Colors[ImGuiCol_FrameBg] = ImColor(37, 36, 37, 255);
	style->Colors[ImGuiCol_FrameBgActive] = ImColor(37, 36, 37, 255);
	style->Colors[ImGuiCol_FrameBgHovered] = ImColor(37, 36, 37, 255);

	style->Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_HeaderHovered] = ImColor(46, 46, 46, 255);
}