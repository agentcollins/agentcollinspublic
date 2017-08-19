import nltk

class Analyzer():
    """Implements sentiment analysis."""

    #define intilization state
    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        #setup lists for positive and negative words that are accessible to analyze function as well
        self.positives = []
        self.negatives = []

        #open incoming positve list into 'good'
        with open(positives) as good:
            #iterate through each line
            for line in good:
                #filter out comment lines and blank lines
                if not line.startswith(';') and not line.startswith('\n'):
                    #add word to positive list, stripping leading and trailing whitespace
                    self.positives.append(line.strip())
        #close positive file
        good.close()

        #repeat same process as above for negative file
        with open(negatives) as bad:
            for line in bad:
                if not line.startswith(';') and not line.startswith('\n'):
                    self.negatives.append(line.strip())
        bad.close()

    #define analyze function
    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        #capture passed in text
        self.text = text
        #intialize sentiment score to zero
        score = 0
        #create tweet token object, striping handles and converting to all lowercase
        tokenizer = nltk.tokenize.TweetTokenizer(strip_handles=True, preserve_case=False)
        #tokenize text (split string into list of words)
        tokens = tokenizer.tokenize(self.text)

        #iterate over each word
        for words in tokens:
            #evalutate against positive list
            if words in self.positives:
                #adjust overall score
                score += 1
            #evaluate against negative list
            elif words in self.negatives:
                #adjust overall score
                score -= 1

        #return the final score for the entire passed in text
        return score
