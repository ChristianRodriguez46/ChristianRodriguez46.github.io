function Card(suit, type){
    this.suit = suit;
    this.type = type;
    
    this.getValue = function(){
        switch (this.type) {
            case "Ace":
                return 11;
            case "Jack":
            case "Queen":
            case "King":
                return 10;
            default:
                return parseInt(this.type);
        }
    }

    this.toString = function(){
        return "The " + this.type + " of " + this.suit;
    }

    this.imgUrl = function(){
        return "./cards/" + this.suit + "/" + this.type + ".png";
    }
}

function Deck(){
    let suits = ["clubs", "diamonds", "hearts", "spades"];
    let types = [2,3,4,5,6,7,8,9,10,"Jack","Queen","King","Ace"];
    let cards = [];

    for(let suit of suits){
        for(let type of types){
            cards.push(new Card(suit, type));
        }
    }

    // Randomly shuffle array of cards
    cards.sort(function() { return 0.5 - Math.random(); });
    this.cards = cards;
}