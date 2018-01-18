function Polis (){
    var maptiles;

    var tileIDs = {
        wood: 0,
        food: 1,
        stone: 2,
        gold: 3,
        none: 4,
        gatherer: 5,
    };
    
    var tileOffsets = {
        0: 4,
        1: 108,
        2: 10,
        3: 302,
        4: 2,
        5: 7
    }

    var resources = [0, 0, 0, 0];

    this.map = [];
    particles = [];
//    this.resourceTiles = [new Sprite()]
    this.setup = function()
    {
        this.tiles = new jaws.SpriteSheet({image: "tileset.png", frame_size: [32, 32], scale_image: 1, orientation: "right"});

        var tiles = this.tiles;

        for (i = 0; i < 23 * 24; i += 1)
        {
            var number = Math.random();
            var res = -1;
            if (number < 0.1)
            {
                res = tileIDs.gold;
            }
            else if (number < 0.25)
            {
                res = tileIDs.stone;
            }
            else if (number < 0.5)
            {
                res = tileIDs.wood;
            }
            else if (number < 0.65)
            {
                res = tileIDs.food;
            }
            else
            {
                res = tileIDs.none;
            }
            var tmpObj = createObject({components: {position: new cPosition(Math.floor(i % 24) * 32, 32 + (Math.floor(i / 24) * 32)),
                                                    drawable: new cDrawable(this.tiles.frames[tileOffsets[res]]), resource: new cResource(res)}}, this.map);
            this.map.push(tmpObj);
        }
        
        var tmp = createObject({components: {position: new cPosition(2 * 32, 3 * 32), resourcegatherer: new cResourceGatherer(), drawable: new cDrawable(this.tiles.frames[tileOffsets[tileIDs.gatherer]])}}, this.map);

        particles.push(createObject({components: {position: new cPosition(64, 128), particle: new cTextParticle("+1", 60)}}))
        this.map[50] = tmp;
    };
    
    this.update = function()
    {
        _.each(this.map, function(elm, idx, l){elm.update();});
        _.each(particles, function(elm, idx, l){elm.update();});
    };
    
    this.draw = function()
    {
        jaws.context.fillStyle = "#74cf45";
        jaws.context.fillRect(0, 0, 768, 768);
        _.each(this.map, function(elm, idx, l)
               {elm.draw();});
        
        _.each(particles, function(elm, idx, l)
               {elm.draw();});

        jaws.context.fillStyle = "#691f01";
        jaws.context.fillRect(0, 0, 768, 32);
        jaws.context.fillStyle = "white";
        jaws.context.font = "28px Serif";
        jaws.context.fillText("Wood: " + resources[tileIDs.wood] + " Food: " + resources[tileIDs.food] + " Stone: " + resources[tileIDs.stone] + " Gold: " + resources[tileIDs.gold], 8, 30);
        
    };

    document.onclick = function() {alert(jaws.mouse_x);};
    
    function createObject(o, map)
    {
        function componentDraw()
        {
            _.each(this.components, function(elm, idx, l)
                   { if (elm.draw) { elm.draw();} });
        };

        function componentUpdate()
        {
            _.each(this.components, function(elm, idx, l)
                   { if (elm.update) { elm.update();} });
        };
        function componentClaim(o)
        {
            _.each(o.components, function(elm, idx, l)
                   { elm.owner = o });
        };
        
        var ret = o;

        componentClaim(ret);
        ret.draw = _.bind(componentDraw, ret);
        ret.update = _.bind(componentUpdate, ret);
        ret.map = map;
        return ret;
    };
    
    function cPosition(x, y)
    {
        this.x = x;
        this.y = y;
    };

    function cDrawable(sprite)
    {
        this.sprite = new jaws.Sprite({image: sprite});

        this.draw = function()
        {
            this.sprite.x = this.owner.components.position.x;
            this.sprite.y = this.owner.components.position.y;
            this.sprite.draw();
        }
    };

    function positionToIndex(row, col, rowLength)
    {
        return Math.floor(row * rowLength) + col;
    }

    function cResource(r)
    {
        this.resource = r;
    }

    function cTextParticle(text, lifespan)
    {
        this.text = text;
        this.lifespan = lifespan;
        var lifeInterval = (1.0 / lifespan)
        var opacity = 1.0;
        
        this.update = function()
        {
            if (opacity <= 0)
            {
                console.log("map before");
                console.log(particles)
                particles.splice(_.indexOf(particles, this), 1);
                console.log("map after: ");
                console.log(particles);
            }
            this.owner.components.position.y -= 2;
            opacity -= lifeInterval;
        }
        
        this.draw = function()
        {
            jaws.context.fillStyle = "rgba(255, 255, 0, " + opacity  + ")"
            jaws.context.text = "12px Serif";
            jaws.context.fillText(text, this.owner.components.position.x, this.owner.components.position.y);
        }
    }
    
    function cResourceGatherer()
    {
        this.interval = 5000;
        this.time = 0;
        this.efficiency = 1;

        this.update = function()
        {
            this.time += jaws.game_loop.tick_duration;

            if (this.time >= this.interval)
            {
                this.proc();
                this.time = 0;
            }
        }
        
        this.proc = function()
        {
            var index = positionToIndex(Math.floor(this.owner.components.position.x / 32), Math.floor((this.owner.components.position.y - 32) / 32), 24)
            var adjacentTiles = [this.owner.map[index - 1], this.owner.map[index - 24], this.owner.map[index + 1], this.owner.map[index + 24]];
            _.each(adjacentTiles, function(elm, idx, l)
                   {
                       if (elm.components.resource)
                       {
                           var rsc = elm.components.resource;
                           resource = rsc.resource;
                           if (resource == tileIDs.food || resource == tileIDs.wood || resource == tileIDs.stone || resource == tileIDs.gold)
                           {
                               resources[resource] += 1;
                           }
                       }
                   })
        }
    }
}


