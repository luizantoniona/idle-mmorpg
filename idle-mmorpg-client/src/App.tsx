import { BrowserRouter as Router, Routes, Route, Navigate } from "react-router-dom";
import { useAuth, AuthProvider } from "./context/AuthContext";
import { ServerProvider } from "./context/ServerContext";
import { AccountPage, LoginPage, GamePage } from "./pages";

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
