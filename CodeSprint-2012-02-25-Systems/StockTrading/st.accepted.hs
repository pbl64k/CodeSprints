
import Data.List

parts :: [Integer] -> [[(Integer, Integer)]]
parts ps = foldl' f [] (reverse ps)
    where 
        f [] price = [(price, price)] : []
        f result@(cur@((price', maxprice) : _) : rest') price | price > maxprice = [(price, price)] : result
                                                              | otherwise = ((price, maxprice) : cur) : rest'

sol = sum . (map (sum . (map (uncurry $ flip (-)))))

explode = unfoldr f
    where f str = let (chunk, rest) = span (/= ' ') str in if null chunk then Nothing else if null rest then Just (chunk, rest) else Just (chunk, tail rest)

tst = getLine >> getLine >>= (putStrLn . show . sol . parts . (map read) . explode)

main = getLine >>= (\t -> mapM_ (const tst) [1 .. (read t)])

