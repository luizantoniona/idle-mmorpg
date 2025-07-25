import { BrowserRouter as Router, Routes, Route, Navigate } from "react-router-dom";
import { AuthProvider } from "./contexts/AuthContext";
import { ServerProvider } from "./contexts/ServerContext";
import { AccountPage, LoginPage, GamePage } from "./components/pages";
import { useAuth } from "./contexts/AuthContext";

function PrivateRoute({ children }: { children: React.ReactNode }) {
  const { isLoggedIn } = useAuth();
  return isLoggedIn() ? <>{children}</> : <Navigate to="/" replace />;
}

export default function App() {
  return (
    <ServerProvider>
      <AuthProvider>
        <Router>
          <Routes>
            <Route path="/" element={<LoginPage />} />
            <Route path="/account" element={
              <PrivateRoute>
                <AccountPage />
              </PrivateRoute>
            }
            />
            <Route path="/game" element={
              <PrivateRoute>
                <GamePage />
              </PrivateRoute>
            }
            />
          </Routes>
        </Router>
      </AuthProvider>
    </ServerProvider>
  );
}
