using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace JumpGame
{
	public class Text : DrawableGameComponent
	{
		private Jump game;
		private Vector2 location;
		private SpriteFont font;
		private Color color;
		private string content;

		public string Content
		{
			get { return content; }
			set { content = value; }
		}

		public Vector2 Location
		{
			get { return location; }
			set { location = value; }
		}

		public Text(Jump game, string content, Vector2 location, Color color) : base(game)
		{
			this.game = game;
			this.content = content;
			this.location = location;
			this.color = color;
		}

		public void OtherLoadContent(string fontName)
		{
			font = game.Content.Load<SpriteFont>(fontName);
		}

		protected override void LoadContent()
		{
			font = game.Content.Load<SpriteFont>("monof_24");
		}

		public void InnerDraw(GameTime gt)
		{
			game.batch.DrawString(font, content, location, color);
		}

		public override void Draw(GameTime gt)
		{
			SpriteBatch sprite = this.game.batch;
			sprite.Begin();
			game.batch.DrawString(font, content, location, color);
			sprite.End();
		}
	}
}
