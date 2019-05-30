/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef SUPERNOVA2_STATE_H
#define SUPERNOVA2_STATE_H

#include "common/events.h"
#include "common/rect.h"
#include "common/keyboard.h"
#include "supernova2/rooms.h"
//#include "supernova2/sound.h"

namespace Supernova2 {

const int32 kMaxTimerValue = 0x7FFFFFFF;

struct GameState {
};

class Inventory {
public:
	Inventory(Object *nullObject, int &inventoryScroll)
		: _numObjects(0)
		, _nullObject(nullObject)
	    , _inventoryScroll(inventoryScroll) {
		for (int i = 0; i < kMaxCarry; ++i)
			_inventory[i] = nullptr;
	}

	void add(Object &obj);
	void remove(Object &obj);
	void clear();
	Object *get(int index) const;
	Object *get(ObjectId id) const;
	int getSize() const { return _numObjects; }

private:
	Object *_inventory[kMaxCarry];
	Object *_nullObject;
	int &_inventoryScroll;
	int _numObjects;
};

class GuiElement : public Common::Rect {
public:
	GuiElement();

	void setSize(int x1, int y1, int x2, int y2);
	void setText(const char *text);
	void setTextPosition(int x, int y);
	void setColor(int bgColor, int textColor, int bgColorHighlighted, int textColorHightlighted);
	void setHighlight(bool isHighlighted);

	const char *getText() const {
		return _text;
	}
	int getBackgroundColor() const {
		return _bgColor;
	}
	int getTextColor() const {
		return _textColor;
	}
	const Common::Point &getTextPos() const {
		return _textPosition;
	}
	bool isHighlighted() const {
		return _isHighlighted;
	}

private:
	Common::Point _textPosition;
	char _text[128];
	int _bgColor;
	int _textColor;
	int _bgColorNormal;
	int _bgColorHighlighted;
	int _textColorNormal;
	int _textColorHighlighted;
	bool _isHighlighted;
};

class GameManager {
public:
	GameManager(Supernova2Engine *vm);
	~GameManager();

	void updateEvents();
	void processInput(Common::KeyState &state);
	void processInput();
	void executeRoom();

	static StringId guiCommands[];
	static StringId guiStatusCommands[];
	Supernova2Engine *_vm;
	Common::KeyState _key;
	Common::EventType _mouseClickType;
	bool _mouseClicked;
	bool _keyPressed;
	int _mouseX;
	int _mouseY;
	int _mouseField;
	Room *_currentRoom;
	bool _newRoom;
	Room *_rooms[NUMROOMS];
	Inventory _inventory;
	GameState _state;
	bool _processInput;
	bool _guiEnabled;
	bool _animationEnabled;
	Action _inputVerb;
	Object _nullObject;
	Object *_currentInputObject;
	Object *_inputObject[2];
	int32 _oldTime;
	uint _timePaused;
	bool _timerPaused;
	int32 _messageDuration;
	int32 _animationTimer;
	int _inventoryScroll;
	int _exitList[25];
	GuiElement _guiCommandButton[10];
	GuiElement _guiInventory[8];
	GuiElement _guiInventoryArrow[2];
	// Dialog
	int _currentSentence;
	int _sentenceNumber[6];
	StringId _texts[6];
	byte _rows[6];
	byte _rowsStart[6];

	void takeObject(Object &obj);
	void setObjectNull(Object *&obj);
	bool isNullObject(Object *obj);

	void initState();
	void initRooms();
	void destroyRooms();
	void initGui();
	bool genericInteract(Action verb, Object &obj1, Object &obj2);
	uint16 getKeyInput(bool blockForPrintChar = false);
	void getInput();
	void wait(int ticks);
	void waitOnInput(int ticks);
	bool waitOnInput(int ticks, Common::KeyCode &keycode);
	void showMenu();
	int invertSection(int section);
	void drawMapExits();
	void drawStatus();
	void drawCommandBox();
	void drawInventory();
	void changeRoom(RoomId id);
	void resetInputState();
	void handleInput();
	void handleTime();
	void setAnimationTimer(int ticks);
	int  dialog(int num, byte rowLength[6], StringId text[6], int number);
	void sentence(int number, bool brightness);
	void say(StringId textId);
	void say(const char *text);
	void reply(StringId textId, int aus1, int aus2);
	void reply(const char *text, int aus1, int aus2);
	void mousePosDialog(int x, int y);

private:
	int _prevImgId;
};

}

#endif // SUPERNOVA2_STATE_H