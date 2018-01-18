using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System.Collections.Generic;

namespace JumpGame
{
	public class Block : JumpSprite
	{
		private Color color;
		private Block partner = null;

		//Speed is pixels per second.
		private int xSpeed = 0;
	    private int ySpeed = 0;
		private int leftOverTimeX = 0;
		private int leftOverTimeY = 0;
		private bool hit = false;
        
		public Block(Jump game, ILevel level, Rectangle blockRect, Color color, int ySpeed) : base(game)
		{
			this.game = game;
			this.rect = blockRect;
			this.color = color;
			this.ySpeed = ySpeed == 0 ? 0 : (1000 / ySpeed);
            this.level = level;
		}

		public Block(Jump game, ILevel level, Rectangle blockRect, Color color, int xSpeed, int ySpeed) : base(game)
		{
			this.game = game;
			this.rect = blockRect;
			this.color = color;
			this.xSpeed = xSpeed == 0 ? 0 : (1000 / xSpeed);
			this.ySpeed = ySpeed == 0 ? 0 : (1000 / ySpeed);
            this.level = level;
		}

		protected override void LoadContent()
		{
			CreateTexture(rect.Width, rect.Height, game.graphics);
		}

		public void Hit()
		{
			if ((partner != null && !partner.hit && !hit) 
				|| (partner == null && !hit))
			{
				level.AddPoints(Math.Max(Math.Abs(xSpeed), Math.Abs(ySpeed)));
			}

			hit = true;
		}

		public void SetPartner(Block partnerBlock)
		{
			partner = partnerBlock;
			partnerBlock.partner = this;
		}

		public override void Update(GameTime gt)
		{
			CalculateAndMoveX(gt);
			CalculateAndMoveY(gt);

            List<Block> blocks = level.GetBlocks();
            for (int i = 0; i < blocks.Count; i++)
            {
                Block b = blocks[i];
                if (b != this)
                {
                    if (this.Collides(b))
                    {
                        if (this.rect.Y > b.rect.Y)
                        {
                            game.Components.Remove(this);
                            level.GetBlocks().Remove(this);
                        }
                    }
                }
            }
			if (rect.Y > game.graphics.PreferredBackBufferHeight || rect.X > game.graphics.PreferredBackBufferWidth)
			{
				game.Components.Remove(this);
                level.GetBlocks().Remove(this);
			}
		}

		public int GetXSpeed(GameTime gt)
		{
			int totalTime = (gt.ElapsedGameTime.Milliseconds + leftOverTimeX);
			return xSpeed != 0 ? totalTime / xSpeed : 0;
		}

		public int GetYSpeed(GameTime gt)
		{
			int totalTime = (gt.ElapsedGameTime.Milliseconds + leftOverTimeY);
            return ySpeed != 0 ? totalTime / ySpeed : 0;
		}

		private void CalculateAndMoveX(GameTime gt)
		{
			if (xSpeed == 0)
				return;
			
			int totalTime = (gt.ElapsedGameTime.Milliseconds + leftOverTimeX);
			int dropAmount = totalTime / xSpeed;

			leftOverTimeX = totalTime % xSpeed;
			rect = new Rectangle(rect.X + dropAmount, rect.Y, rect.Width, rect.Height);
		}

		private void CalculateAndMoveY(GameTime gt)
		{
			if (ySpeed == 0)
				return;
			
			int totalTime = (gt.ElapsedGameTime.Milliseconds + leftOverTimeY);
			int dropAmount = totalTime / ySpeed;

			leftOverTimeY = totalTime % ySpeed;
			rect = new Rectangle(rect.X, rect.Y + dropAmount, rect.Width, rect.Height);
		}

		private void CreateTexture(int width, int height, GraphicsDeviceManager g)
		{
			tex = new Texture2D(g.GraphicsDevice, width, height);
			Color[] data = new Color[width*height];

			for (int i = 0; i < data.Length; ++i)
			{
				data [i] = color;
			}

			tex.SetData(data);
		}
	}
}
