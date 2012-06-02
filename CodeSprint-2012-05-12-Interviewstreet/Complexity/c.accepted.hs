
import Data.Char
import Data.HashTable
import Data.IORef
import Data.Maybe
import qualified System.IO
import Text.ParserCombinators.Parsec

data Expr = Num Int | Ident Int | XMul Expr Expr | XDiv Expr Expr | XAdd Expr Expr | XSub Expr Expr deriving Show

data Cond = Lt Expr Expr | Gt Expr Expr | Eq Expr Expr | Ne Expr Expr | XCond Expr deriving Show

data Decl = DList [Int] deriving Show

data Stmt = Nil | Assgn Int Expr | Wh Cond Stmt | For Stmt Cond Stmt Stmt | Bl [Stmt] deriving Show

data Program = P Decl Stmt deriving Show

prs p = (\(Right x) -> x) . (parse p "!")

program = do
            d <- declaration
            l <- many statement
            eof
            return (P d (Bl l))

declaration = do
                spaces
                l <- identifier `sepEndBy` spaces
                spaces
                terminator
                return (DList (map (\(Ident x) -> x) l))

statement = (try block) <|> (try for) <|> (try while) <|> (try assignment) <|> (terminator >> (return Nil))

block = do
          l <- (try $ between open_brace close_brace (many statement)) <|> (try $ between open_brace close_brace block')
          return (Bl l)

block' = do
            l <- many statement
            l' <- assignment'
            return (l ++ [l'])

for = do
          spaces
          string "for"
          spaces
          open_paren
          a1 <- (try assignment') <|> (return Nil)
          colon
          c <- cond
          colon
          a2 <- (try assignment') <|> (return Nil)
          close_paren
          spaces
          b <- statement
          spaces
          return (For a1 c a2 b)

while = do
          spaces
          string "while"
          spaces
          c <- between open_paren close_paren cond
          spaces
          b <- statement
          spaces
          return (Wh c b)

assignment = do
               a <- assignment'
               terminator
               return a

assignment' = do
               spaces
               (Ident l) <- identifier
               sc '='
               r <- expr
               spaces
               return (Assgn l r)

--cond = (try paren_cond) <|> (try (bin_op x_cond f_cond expr expr)) <|> cond_expr
cond = (try paren_cond) <|> (bin_op x_cond f_cond expr expr)

paren_cond = between open_paren close_paren cond

cond_expr = do
              x <- expr
              return (XCond x)

expr = (try $ add_expr expr) <|> (try $ mul_expr expr) <|> (try paren_expr) <|> (try identifier) <|> number
non_add_expr = (try $ mul_expr non_add_expr) <|> (try paren_expr) <|> (try identifier) <|> number
non_mul_expr = (try paren_expr) <|> (try identifier) <|> number

add_expr x = bin_op x_addsub (oneOf "+-") non_add_expr x
mul_expr x = bin_op x_muldiv (oneOf "*/") non_mul_expr x

paren_expr = between open_paren close_paren expr

open_brace = sc '{'
close_brace = sc '}'
open_paren = sc '('
close_paren = sc ')'

identifier = (try n_identifier) <|> a_identifier

n_identifier = do
                 char 'N'
                 return (Ident (-1))

a_identifier = do
                 c <- oneOf "abcdefghijklmnopqrstuvxyzABCDEFGHIJKLMNOPQRSTUVXYZ"
                 x <- many digit
                 let x' = if null x then "0" else x
                 return (Ident $ (read x) + ((ord c) * 100))

number = do
           x <- many1 digit
           return (Num $ read x)

colon = sc ':'
terminator = sc ';'

f_cond = (try lt) <|> (try gt) <|> (try eq) <|> ne

lt = do
       (try $ string "&lt;") <|> string "<"
       return '<'
gt = do
       (try $ string "&gt;") <|> string ">"
       return '>'
eq = do
       string "=="
       return '='
ne = do
       string "!="
       return '!'
           
x_cond '<' = Lt
x_cond '>' = Gt
x_cond '=' = Eq
x_cond '!' = Ne

x_addsub '+' = XAdd
x_addsub '-' = XSub
x_muldiv '*' = XMul
x_muldiv '/' = XDiv

bin_op c ch xl xr = do
                  spaces
                  x1 <- xl
                  spaces
                  op_c <- ch
                  spaces
                  x2 <- xr
                  spaces
                  return (c op_c x1 x2)

sc c = do
         spaces
         char c
         spaces

evalCond :: HashTable Int Int -> Cond -> IO Bool
evalCond vars (Lt x1 x2) = evalX vars x1 x2 (<)
evalCond vars (Gt x1 x2) = evalX vars x1 x2 (>)
evalCond vars (Eq x1 x2) = evalX vars x1 x2 (==)
evalCond vars (Ne x1 x2) = evalX vars x1 x2 (/=)
evalCond vars (XCond x) = do
                            v <- evalExpr vars x
                            return (v /= 0)

evalExpr :: HashTable Int Int -> Expr -> IO Int
evalExpr vars (Num x) = return x
evalExpr vars (Ident x) = do
                            v <- Data.HashTable.lookup vars x
                            return (fromMaybe 0 v)
evalExpr vars (XMul x1 x2) = evalX vars x1 x2 (*)
evalExpr vars (XDiv x1 x2) = evalX vars x1 x2 div
evalExpr vars (XAdd x1 x2) = evalX vars x1 x2 (+)
evalExpr vars (XSub x1 x2) = evalX vars x1 x2 (-)

evalX vars x1 x2 f = do
                       v1 <- evalExpr vars x1
                       v2 <- evalExpr vars x2
                       return (f v1 v2)

eval cnt vars Nil = return ()

eval cnt vars (Assgn k x) = do
                              v <- evalExpr vars x
                              update vars k v
                              modifyIORef cnt (+ 1)

eval cnt vars w@(Wh c b) = do
                           f <- evalCond vars c
                           if f then ((eval cnt vars b) >> (eval cnt vars w)) else return ()

eval cnt vars (For a1 c a2 b) = do
                                  eval cnt vars a1
                                  f <- evalCond vars c
                                  if f then ((eval cnt vars b) >> (eval cnt vars a2) >> (eval cnt vars (For Nil c a2 b))) else return ()

eval cnt vars (Bl []) = return ()

eval cnt vars (Bl (s : ss)) = do
                                eval cnt vars s
                                eval cnt vars (Bl ss)

brrrng n block = do
                   cnt <- newIORef 0
                   vars <- new (==) hashInt
                   update vars (-1) n
                   eval cnt vars block
                   cnt' <- readIORef cnt
                   return cnt'

--ff l = all (== 0) l
ff l = let ll = filter (== 0) l in (length ll) >= ((length l) `div` 3)

diffs' n [] = n
diffs' n l = if ff l then (n - 1) else diffs' (n + 1) (diffs l)

diffs l = map (max 0) (zipWith (-) (tail l) l)

main = do
         p <- getContents
         let (P decl block) = prs program p
         l <- mapM (\n -> brrrng n block) [1 .. 20]
         --putStrLn (show $ l)
         putStrLn (show $ diffs' 0 l)

