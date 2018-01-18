using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace JumpGame
{

    public class LevelM : ILevel
    {
        private class Button : Block
        {
            public Text text;
            private int lvl;

            public Button(Jump game, ILevel level, Rectangle blockRect, Color color, string txt, int lvl)
            : base(game, level, blockRect, color, 0)
            {
                this.text = new Text(game, txt, new Vector2(blockRect.X, blockRect.Y),
                                     Color.Black);

                this.lvl = lvl;
            }

            public override void Update(GameTime gt)
            {
                MouseState m = Mouse.GetState();
                if (m.LeftButton == ButtonState.Pressed)
                {
                    Console.WriteLine("Mouse is pressed " + m.X + " " + m.Y);
                    if (JumpSprite.RectCollides(new Rectangle(m.X, m.Y, 10, 10), this.rect)
                        || JumpSprite.RectCollides(this.rect, new Rectangle(m.X, m.Y, 10, 10)))
                    {
                        Console.WriteLine("Collision");
                        switch (lvl)
                        {
                        case 1:
                            this.game.level = new Level1(game);
                            break;
                        case 2:
                            this.game.level = new Level2(game);
                            break;
							case 3:
								this.game.level = new Level3 (game);
							break;
/*                    case 1:
                      this.game.level = new Level1(game);
                      break;*/
                        }
                        this.level.End();
                    }
                }
            }
        }
        
        private Button[] buttons;
        private Jump game;

        public LevelM(Jump game)
        {
            this.game = game;
        }
        public void Init()
        {
            this.game.IsMouseVisible = true;
            this.buttons = new Button[3];
            this.buttons[0] = new Button(game, this, new Rectangle(100, 352, 200, 64),
                                         Color.RoyalBlue, "Mode 1", 1);

            this.game.Components.Add(this.buttons[0]);
            this.game.Components.Add(this.buttons[0].text);

            this.buttons[1] = new Button(game, this, new Rectangle(350, 352, 200, 64),
                                             Color.Cyan, "Mode 2", 2);
            this.game.Components.Add(this.buttons[1]);
            this.game.Components.Add(this.buttons[1].text);

			this.buttons[2] = new Button(game, this, new Rectangle(600, 352, 200, 64),
				Color.SpringGreen, "Mode 3", 3);
			this.game.Components.Add(this.buttons[2]);
			this.game.Components.Add(this.buttons[2].text);

        }

        public List<Block> GetBlocks()
        {
            return null;
        }
        public void End()
        {
            this.game.IsMouseVisible = false;
            foreach (Button b in this.buttons)
            {
                this.game.Components.Remove(b.text);
                this.game.Components.Remove(b);
            }
        }

        public void Tick()
        {}
        public void AddPoints(int no)
        {}
    }
}