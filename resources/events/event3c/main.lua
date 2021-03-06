event3c = LuaEvent.new("event3c")

event3c.init = function()
	event3c = event3c:initEvent()

	event3c.update = function()
		if ResourceHelper.getPlayer():inFrontOf(event3c.event)
		and Keyboard.isKeyPressedOnce(Keyboard.GameAttack) then
			event3c.event:face(ResourceHelper.getPlayer())

			event3c:addAction(0, LuaEvent.drawText, _t("event3c-0"), 1)
			event3c:addAction(1, LuaEvent.askQuestion, _t("event3c-1"),
							  _t("Yes"), 2,
							  _t("No"), 3)
			event3c:addAction(2, LuaEvent.drawText, _t("event3c-2"), -1)
			event3c:addAction(3, LuaEvent.askQuestion, _t("event3c-3"),
							  _t("Yes"), 4,
							  _t("No"), 1)
			event3c:addAction(4, LuaEvent.drawText, _t("event3c-4"), 5)
			event3c:addAction(5, LuaEvent.startBattle, 1, true, 6, 7, 8)
			event3c:addAction(6, LuaEvent.drawText, "Aaaaaaaaaaarg!!!", -1)
			event3c:addAction(7, LuaEvent.drawText, "Tsssssssss...", -1)
			event3c:addAction(8, LuaEvent.drawText, "Muhahahahaha", -1)
		end
	end

	event3c.movements = {
		function() event3c.event:moveLeft() end,
		function() event3c.event:moveUp() end,
		function() event3c.event:moveRight() end,
		function() event3c.event:moveDown() end
	}
end

