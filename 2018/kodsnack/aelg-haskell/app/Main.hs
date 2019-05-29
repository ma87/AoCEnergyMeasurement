module Main
  ( main
  ) where

import           Data.ByteString.Char8 (pack, unpack)
import           Data.CaseInsensitive  (mk)
import qualified Data.Map              as M
import           Data.Maybe
import           Network.HTTP.Client
import           Network.HTTP.Client.TLS
import           System.Environment
import           System.Directory
import           Control.Exception
import           Control.Parallel.Strategies

import qualified Day01
import qualified Day02
import qualified Day03
import qualified Day04
import qualified Day05
import qualified Day06
import qualified Day07
import qualified Day08
import qualified Day09
import qualified Day10
import qualified Day11
import qualified Day12
import qualified Day13
import qualified Day14
import qualified Day15
import qualified Day16
import qualified Day17
import qualified Day18

solved =
  M.fromList
    [ (1, Day01.solve)
    , (2, Day02.solve)
    , (3, Day03.solve)
    , (4, Day04.solve)
    , (5, Day05.solve)
    , (6, Day06.solve)
    , (7, Day07.solve)
    , (8, Day08.solve)
    , (9, Day09.solve)
    , (10, Day10.solve)
    , (11, Day11.solve)
    , (12, Day12.solve)
    , (13, Day13.solve)
    , (14, Day14.solve)
    , (15, Day15.solve)
    , (16, Day16.solve)
    , (17, Day17.solve)
    , (18, Day18.solve)
    ]

getSolution x = M.findWithDefault notImplemented x solved

solve :: Int -> ([String] -> (String, String)) -> String -> String
solve x f s =
  "Day " ++ show x ++ ":\n"
  ++ "  " ++ a1 ++ "\n"
  ++ "  " ++ a2 ++ "\n"
  where
    (a1, a2) = f . lines $ s

notImplemented s = ("Not implemented", "Input: " ++ unlines s)

createCacheDir = createDirectoryIfMissing False ".cache"

cacheName ms = ".cache/input-" ++ show ms ++ ".txt"

readInput :: String -> Int -> IO String
readInput session ms = try cache >>= either (const download :: IOException -> IO String) return
  where
    download = do
      initRequest <-
        parseRequest $ "http://adventofcode.com/2018/day/" ++ show ms ++ "/input"
      let session' = "session=" ++ session
          req = initRequest {requestHeaders = [(mk $ pack "Cookie", pack session')]}
      manager <- newTlsManager
      s <- withResponse req manager (brConsume . responseBody)
      let input = concatMap unpack s
      writeFile (cacheName ms) input
      return input
    cache = do
      createCacheDir
      readFile $ cacheName ms

maybeRead = fmap fst . listToMaybe . reads

main = do
  arg <- fmap listToMaybe getArgs
  sessionKey <- fmap (head . lines) . readFile $ "sessionKey.txt"
  let ms = arg >>= maybeRead :: Maybe Int
      s = readInput sessionKey
  inputs <- mapM s (M.keys solved)
  let solvers =
        case ms of
          Just x -> [solve x (getSolution x) $ inputs !! (x-1)]
          _      -> map (\(x, input) -> solve x (getSolution x) input) (zip [1..] inputs)
  mapM_ putStr (solvers `using` parTraversable rdeepseq)

