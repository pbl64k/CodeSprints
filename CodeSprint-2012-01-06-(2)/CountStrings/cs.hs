
import Data.List
import Data.Word
import Text.ParserCombinators.Parsec

data MInt = M Word64

mw = 1000000007

m = (`mod` mw)

m' = M . m

readMInt = M . read

instance Show MInt where

    show (M i) = show i

instance Enum MInt where

    succ (M i) = m' $ succ i
    pred (M i) = m' $ pred i
    toEnum i = m' $ toEnum i
    fromEnum (M i) = fromEnum i

instance Eq MInt where

    (M i1) == (M i2) = i1 == i2

instance Ord MInt where

    (M i1) `compare` (M i2) = i1 `compare` i2

instance Num MInt where

    (M i1) + (M i2) = m' $ i1 + i2
    (M i1) * (M i2) = m' $ i1 * i2
    (M i1) - (M i2) = m' $ i1 - i2
    abs (M i) = m' $ abs i
    signum (M i) = m' $ signum i
    fromInteger i = m' $ fromInteger i

instance Real MInt where

    toRational (M i) = toRational i

instance Integral MInt where

    quotRem (M i1) (M i2) = (M $ i1 `div` i2, M $ i1 `mod` i2)
    toInteger (M i) = toInteger i

data Exp = A | B | Sq Exp Exp Bool [(MInt, MInt)] | Opt Exp Exp Bool [(MInt, MInt)] | Rpt Exp Bool [(MInt, MInt)] deriving Show

mk'sq r1 r2 = let ff = (fin r1) && (fin r2)
                  in if ff then Sq r1 r2 True (lens'sq r1 r2) else Sq r1 r2 False []
mk'opt r1 r2 = let ff = (fin r1) && (fin r2)
                  in if ff then Opt r1 r2 True (lens'opt r1 r2) else Opt r1 r2 False []
mk'rpt r1 = Rpt r1 False []

lens'sq r1 r2 = lens'sq' (fxl r1) (fxl r2)

lens'sq' r1 r2 = let cart = [(len1 + len2, comb1 * comb2) | (len1, comb1) <- r1, (len2, comb2) <- r2]
                     nonu = sortBy (\(len1, _) (len2, _) -> len1 `compare` len2) cart
                     in len'sq'cmb nonu

len'sq'cmb :: [(MInt, MInt)] -> [(MInt, MInt)]
len'sq'cmb [] = []
len'sq'cmb l@(a : []) = l
len'sq'cmb (p@(len1, comb1) : l@((len2, comb2) : l')) = if len1 == len2 then len'sq'cmb ((len1, comb1 + comb2) : l') else (p : len'sq'cmb l)

lens'opt r1 r2 = lens'opt' (fxl r1) (fxl r2)

lens'opt' [] r2 = r2
lens'opt' r1 [] = r1
lens'opt' r1@(p1@(len1, comb1) : r1') r2@(p2@(len2, comb2) : r2') = if len1 < len2
                                                                       then p1 : (lens'opt' r1' r2)
                                                                       else if len1 > len2
                                                                               then p2 : (lens'opt' r1 r2')
                                                                               else lens'opt' ((len1, comb1 + comb2) : r1') r2'

x (Right a) = a

prs = x . (parse r "!")

a = char 'a' >> return A

b = char 'b' >> return B

sq = try sq'

sq' = do
        char '('
        r1 <- r
        r2 <- r
        char ')'
        return $ mk'sq r1 r2

opt = try opt'

opt' = do
         char '('
         r1 <- r
         char '|'
         r2 <- r
         char ')'
         return $ mk'opt r1 r2

rpt = try rpt'

rpt' = do
         char '('
         r1 <- r
         string "*)"
         return $ mk'rpt r1

r = a <|> b <|> sq <|> opt <|> rpt

cs l str = cs' l (prs str)

fin :: Exp -> Bool
fin A = True
fin B = True
fin (Sq _ _ f _) = f
fin (Opt _ _ f _) = f
fin (Rpt _ _ _) = False

fxl :: Exp -> [(MInt, MInt)]
fxl A = [(1, 1)]
fxl B = [(1, 1)]
fxl (Sq _ _ _ l) = l
fxl (Opt _ _ _ l) = l
fxl (Rpt _ _ l) = l

fxxl l ll = let ll' = dropWhile (\(len, _) -> len < l) ll
                pp = head ll'
                in if (null ll') || ((fst pp) /= l) then 0 else snd pp

cs' :: MInt -> Exp -> MInt
cs' 1 A = 1
cs' _ A = 0
cs' 1 B = 1
cs' _ B = 0
cs' l (Sq r1 r2 f ll) = if f then fxxl l ll else cs'sq l r1 r2
cs' l (Opt r1 r2 f ll) = if f then fxxl l ll else (cs' l r1) + (cs' l r2)
cs' l (Rpt r1 _ _) = cs'rpt l r1

cs'sq l r1 r2 = sum $ map (\l' -> (cs' l' r1) * (cs' (l - l') r2)) [0 .. l]

cs'rpt 0 _ = 1
cs'rpt l r1 = sum $ map (\l' -> (cs' l' r1) ^ (l `div` l')) (divs l)

divs l = filter ((== 0) . (l `mod`)) [1 .. l]

main = do
         t <- getLine
         mapM_ (const tst) [1 .. (read t)]

tst = do
        l <- getLine
        let (str, n) = (takeWhile (/= ' ') l, (readMInt . tail) $ dropWhile (/= ' ') l)
        (putStrLn . show) (cs n str)

